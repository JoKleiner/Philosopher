/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joklein <joklein@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/28 14:56:31 by joklein           #+#    #+#             */
/*   Updated: 2025/01/28 15:29:08 by joklein          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi(const char *str)
{
	int		i;
	long	num;

	i = 0;
	num = 0;
	while (str[i] >= '0' && str[i] <= '9')
	{
		num = num * 10 + str[i] - '0';
		if (num > 2147483647)
			return (-1);
		i++;
	}
	return ((int)num);
}

void	init_wait(t_philo *phi_cur)
{
	struct timeval	tv;
	int				cur_time;

	while (1)
	{
		gettimeofday(&tv, NULL);
		cur_time = tv.tv_sec * 1000 + (tv.tv_usec / 1000);
		if (cur_time - 5 >= phi_cur->t_start)
			break ;
		usleep(100);
	}
	if (phi_cur->num % 2 == 0)
		usleep(500);
}

int	mysleep(int wait_time, t_philo *phi_cur)
{
	struct timeval	tv;
	int				cur_time;
	int				start_time;

	gettimeofday(&tv, NULL);
	start_time = tv.tv_sec * 1000 + (tv.tv_usec / 1000);
	while (1)
	{
		pthread_mutex_lock(&phi_cur->block);
		if (phi_cur->status == dead || phi_cur->status == full)
			return (pthread_mutex_unlock(&phi_cur->block), 1);
		pthread_mutex_unlock(&phi_cur->block);
		gettimeofday(&tv, NULL);
		cur_time = tv.tv_sec * 1000 + (tv.tv_usec / 1000);
		if (cur_time - start_time >= wait_time)
			break ;
		usleep(250);
	}
	return (0);
}

void	error_mutex_malloc_init(t_philo *phi_cur)
{
	t_philo	*phi_prev;

	if (phi_cur == NULL)
		return ;
	while (phi_cur->num != 1)
	{
		phi_prev = phi_cur->prev;
		pthread_mutex_destroy(&(phi_cur->fork));
		pthread_mutex_destroy(&(phi_cur->block));
		free(phi_cur);
		phi_cur = NULL;
		phi_cur = phi_prev;
	}
	pthread_mutex_destroy(&(phi_cur->fork));
	pthread_mutex_destroy(&(phi_cur->block));
	pthread_mutex_destroy(&(phi_cur->print));
	free(phi_cur);
	phi_cur = NULL;
}
