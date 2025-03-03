/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joklein <joklein@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 16:21:40 by joklein           #+#    #+#             */
/*   Updated: 2025/01/27 16:27:04 by joklein          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	set_all_dead(t_philo *phi_one)
{
	t_philo	*phi_cur;

	phi_cur = phi_one->next;
	while (phi_cur != phi_one)
	{
		pthread_mutex_lock(&phi_cur->block);
		phi_cur->status = dead;
		pthread_mutex_unlock(&phi_cur->block);
		phi_cur = phi_cur->next;
	}
}

int	set_dead(t_philo *phi_cur, t_philo *phi_one)
{
	struct timeval	tv;
	int				cur_time;

	pthread_mutex_lock(&phi_cur->block);
	gettimeofday(&tv, NULL);
	cur_time = tv.tv_sec * 1000 + (tv.tv_usec / 1000) - 5;
	if (cur_time - phi_cur->last_meal > phi_cur->gen_t_die
		&& phi_cur->eating != eat)
	{
		phi_cur->status = dead;
		set_all_dead(phi_cur);
		pthread_mutex_lock(&phi_one->print);
		gettimeofday(&tv, NULL);
		cur_time = tv.tv_sec * 1000 + (tv.tv_usec / 1000) - 5;
		printf("%d %d died\n", (cur_time - phi_cur->t_start), phi_cur->num);
		pthread_mutex_unlock(&phi_cur->block);
		pthread_mutex_unlock(&phi_one->print);
		return (1);
	}
	pthread_mutex_unlock(&phi_cur->block);
	return (0);
}

void	*monitor_thread(void *philo)
{
	t_philo	*phi_cur;
	t_philo	*phi_one;

	phi_one = (t_philo *)philo;
	while (1)
	{
		phi_cur = phi_one;
		while (phi_cur->next != phi_one)
		{
			if (set_dead(phi_cur, phi_one))
				return (NULL);
			phi_cur = phi_cur->next;
		}
		if (set_dead(phi_cur, phi_one))
			return (NULL);
		if (set_full(phi_cur))
			return (NULL);
		usleep(100);
	}
	return (NULL);
}

int	create_moni_thread(t_philo *phi_one)
{
	t_monitor	*moni;

	moni = (t_monitor *)malloc(sizeof(t_monitor));
	if (!moni)
	{
		set_all_dead(phi_one);
		return (write(1, "Mem alloc went wrong\n", 21), 1);
	}
	if (pthread_create(&moni->threads, NULL, monitor_thread, phi_one) != 0)
	{
		set_all_dead(phi_one);
		return (write(1, "pthread_create failed\n", 22), free(moni), 1);
	}
	pthread_join(moni->threads, NULL);
	free(moni);
	return (0);
}
