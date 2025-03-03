/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_end.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joklein <joklein@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 14:52:58 by joklein           #+#    #+#             */
/*   Updated: 2025/01/27 16:40:47 by joklein          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	set_all_full(t_philo *phi_cur)
{
	t_philo	*phi_one;

	phi_one = phi_cur;
	while (phi_cur->next != phi_one)
	{
		pthread_mutex_lock(&phi_cur->block);
		phi_cur->status = full;
		pthread_mutex_unlock(&phi_cur->block);
		phi_cur = phi_cur->next;
	}
	pthread_mutex_lock(&phi_cur->block);
	phi_cur->status = full;
	pthread_mutex_unlock(&phi_cur->block);
}

int	set_full(t_philo *phi_one)
{
	t_philo	*phi_cur;

	phi_cur = phi_one;
	while (phi_cur->next != phi_one)
	{
		pthread_mutex_lock(&phi_cur->block);
		if (phi_cur->times_eaten < phi_cur->gen_num_eat)
			return (pthread_mutex_unlock(&phi_cur->block), 0);
		pthread_mutex_unlock(&phi_cur->block);
		phi_cur = phi_cur->next;
	}
	pthread_mutex_lock(&phi_cur->block);
	if (phi_cur->times_eaten < phi_cur->gen_num_eat)
		return (pthread_mutex_unlock(&phi_cur->block), 0);
	pthread_mutex_unlock(&phi_cur->block);
	set_all_full(phi_one);
	return (1);
}

int	end_quest(t_philo *phi_cur)
{
	struct timeval	tv;
	int				cur_time;

	gettimeofday(&tv, NULL);
	cur_time = tv.tv_sec * 1000 + (tv.tv_usec / 1000) - 5;
	if (phi_cur->status == dead)
		return (1);
	if (cur_time - phi_cur->last_meal > phi_cur->gen_t_die
		&& phi_cur->eating != eat)
		return (1);
	if (phi_cur->status == full)
		return (1);
	return (0);
}

void	join_philo_thread(t_philo *phi_cur)
{
	while (phi_cur->num != 1)
		phi_cur = phi_cur->next;
	phi_cur = phi_cur->next;
	while (phi_cur->num != 1)
	{
		pthread_join(phi_cur->threads, NULL);
		phi_cur = phi_cur->next;
	}
	pthread_join(phi_cur->threads, NULL);
}

void	detach_philo_thread(t_philo *phi_cur)
{
	phi_cur = phi_cur->prev;
	while (phi_cur->num != 1)
	{
		pthread_mutex_lock(&phi_cur->block);
		pthread_detach(phi_cur->threads);
		pthread_mutex_unlock(&phi_cur->block);
		phi_cur = phi_cur->prev;
	}
	pthread_mutex_lock(&phi_cur->block);
	pthread_detach(phi_cur->threads);
	pthread_mutex_unlock(&phi_cur->block);
}
