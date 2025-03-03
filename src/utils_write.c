/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_write.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joklein <joklein@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 12:38:04 by joklein           #+#    #+#             */
/*   Updated: 2025/01/27 16:21:47 by joklein          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	write_stamp(char *text, t_philo *philo)
{
	t_philo			*phi_one;
	struct timeval	tv;
	int				cur_time;

	phi_one = philo;
	while (phi_one->num != 1)
		phi_one = phi_one->prev;
	pthread_mutex_lock(&phi_one->print);
	if (end_quest(philo) == 1)
		return (pthread_mutex_unlock(&phi_one->print), 1);
	gettimeofday(&tv, NULL);
	cur_time = tv.tv_sec * 1000 + (tv.tv_usec / 1000) - 5;
	if (cur_time - philo->t_start <= 0)
	{
		printf("%d %d %s\n", 0, philo->num, text);
	}
	else
		printf("%d %d %s\n", cur_time - philo->t_start, philo->num, text);
	pthread_mutex_unlock(&phi_one->print);
	return (0);
}

int	write_fork_eat(t_philo *philo)
{
	struct timeval	tv;
	int				cur_time;
	t_philo			*phi_one;

	phi_one = philo;
	while (phi_one->num != 1)
		phi_one = phi_one->prev;
	pthread_mutex_lock(&phi_one->print);
	if (end_quest(philo) == 1)
		return (pthread_mutex_unlock(&phi_one->print), 1);
	gettimeofday(&tv, NULL);
	cur_time = tv.tv_sec * 1000 + (tv.tv_usec / 1000) - 5;
	printf("%d %d %s\n%d %d %s\n", (cur_time - philo->t_start), philo->num,
		"has taken a fork", (cur_time - philo->t_start), philo->num,
		"is eating");
	philo->eating = eat;
	philo->last_meal = cur_time;
	pthread_mutex_unlock(&phi_one->print);
	return (0);
}

void	write_end(t_philo *philo)
{
	struct timeval	tv;
	int				cur_time;

	if (philo->status == dead)
		return ;
	pthread_mutex_lock(&philo->print);
	gettimeofday(&tv, NULL);
	cur_time = tv.tv_sec * 1000 + (tv.tv_usec / 1000) - 5;
	printf("%d %s\n", (cur_time - philo->t_start), "All ate up");
	pthread_mutex_unlock(&philo->print);
	return ;
}
