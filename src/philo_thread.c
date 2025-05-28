/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_thread.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joklein <joklein@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 16:34:19 by joklein           #+#    #+#             */
/*   Updated: 2025/05/28 15:08:44 by joklein          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	unlock_fork(t_philo *phi_cur, t_philo *phi_prev)
{
	pthread_mutex_lock(&phi_cur->block);
	pthread_mutex_unlock(&phi_cur->fork);
	pthread_mutex_unlock(&phi_prev->fork);
	phi_cur->times_eaten++;
	phi_cur->eating = not_eat;
	if (write_stamp("is sleeping", phi_cur) == 1)
		return (pthread_mutex_unlock(&phi_cur->block), 1);
	pthread_mutex_unlock(&phi_cur->block);
	if (mysleep(phi_cur->gen_t_sleep, phi_cur) == 1)
		return (1);
	pthread_mutex_lock(&phi_cur->block);
	if (write_stamp("is thinking", phi_cur) == 1)
		return (pthread_mutex_unlock(&phi_cur->block), 1);
	pthread_mutex_unlock(&phi_cur->block);
	return (0);
}

int	lock_fork(t_philo *phi_cur, t_philo *phi_prev)
{
	if (phi_cur->num % 2 == 0)
	{
		pthread_mutex_lock(&phi_cur->fork);
		pthread_mutex_lock(&phi_cur->block);
		write_stamp("has taken a fork", phi_cur);
		pthread_mutex_unlock(&phi_cur->block);
		pthread_mutex_lock(&phi_prev->fork);
	}
	else
	{
		pthread_mutex_lock(&phi_prev->fork);
		pthread_mutex_lock(&phi_cur->block);
		write_stamp("has taken a fork", phi_cur);
		pthread_mutex_unlock(&phi_cur->block);
		pthread_mutex_lock(&phi_cur->fork);
	}
	pthread_mutex_lock(&phi_cur->block);
	if (write_fork_eat(phi_cur) == 1)
	{
		pthread_mutex_unlock(&phi_cur->fork);
		pthread_mutex_unlock(&phi_prev->fork);
		pthread_mutex_unlock(&phi_cur->block);
		return (1);
	}
	return (pthread_mutex_unlock(&phi_cur->block), 0);
}

void	*philo_thread(void *philo)
{
	t_philo	*phi_cur;
	t_philo	*phi_prev;

	phi_cur = (t_philo *)philo;
	phi_prev = phi_cur->prev;
	pthread_mutex_lock(&phi_cur->block);
	write_stamp("is thinking", phi_cur);
	pthread_mutex_unlock(&phi_cur->block);
	if (phi_cur == phi_cur->next)
		return (write(1, "0 1 has taken a fork\n", 21), NULL);
	init_wait(phi_cur);
	while (1)
	{
		if (lock_fork(phi_cur, phi_prev) == 1)
			return (NULL);
		if (mysleep(phi_cur->gen_t_eat, phi_cur) == 1)
		{
			pthread_mutex_unlock(&phi_cur->fork);
			pthread_mutex_unlock(&phi_prev->fork);
			return (NULL);
		}
		if (unlock_fork(phi_cur, phi_prev) == 1)
			return (NULL);
	}
	return (NULL);
}

int	create_phi_thread(char **argv, t_philo *phi_one)
{
	int		i;
	t_philo	*phi_cur;

	i = 0;
	phi_cur = phi_one;
	while (i < ft_atoi(argv[1]))
	{
		if (pthread_create(&phi_cur->threads, NULL, philo_thread, phi_cur) != 0)
		{
			write(1, "philo pthread create failed\n", 28);
			detach_philo_thread(phi_cur);
			return (1);
		}
		phi_cur = phi_cur->next;
		i++;
	}
	return (0);
}
