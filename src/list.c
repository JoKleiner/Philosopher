/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joklein <joklein@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 14:32:06 by joklein           #+#    #+#             */
/*   Updated: 2025/01/28 15:29:46 by joklein          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_lstclear(t_philo **phi_cur)
{
	t_philo	*temp;
	t_philo	*next;

	while ((*phi_cur)->num != 1)
		*phi_cur = (*phi_cur)->prev;
	temp = (*phi_cur)->next;
	while (temp->num != 1)
	{
		next = temp->next;
		pthread_mutex_destroy(&(temp->fork));
		pthread_mutex_destroy(&(temp->block));
		free(temp);
		temp = NULL;
		temp = next;
	}
	pthread_mutex_destroy(&(temp->fork));
	pthread_mutex_destroy(&(temp->block));
	pthread_mutex_destroy(&temp->print);
	free(temp);
	temp = NULL;
}

t_philo	*ft_lstlast(t_philo *lst)
{
	t_philo	*temp;

	if (!lst)
		return (NULL);
	temp = lst;
	while (temp->next)
		temp = temp->next;
	return (temp);
}

void	ft_lstadd_back(t_philo **lst, t_philo *new)
{
	t_philo	*last;

	if (!*lst)
	{
		*lst = new;
		return ;
	}
	last = ft_lstlast(*lst);
	last->next = new;
	new->prev = last;
	new->next = NULL;
}

t_philo	*ft_lstnew(int phi_num, int start_time)
{
	t_philo	*phi_cur;

	phi_cur = (t_philo *)malloc(sizeof(t_philo));
	if (!phi_cur)
		return (NULL);
	if (pthread_mutex_init(&phi_cur->fork, NULL) != 0)
		return (free(phi_cur), NULL);
	if (pthread_mutex_init(&phi_cur->block, NULL) != 0)
		return (pthread_mutex_destroy(&(phi_cur->fork)), free(phi_cur), NULL);
	if (phi_num == 1)
		if (pthread_mutex_init(&phi_cur->print, NULL) != 0)
			return (pthread_mutex_destroy(&(phi_cur->fork)),
				pthread_mutex_destroy(&(phi_cur->block)), free(phi_cur), NULL);
	phi_cur->num = phi_num;
	phi_cur->next = NULL;
	phi_cur->prev = NULL;
	phi_cur->times_eaten = 0;
	phi_cur->eating = not_eat;
	phi_cur->status = 0;
	phi_cur->t_start = start_time;
	phi_cur->last_meal = start_time;
	return (phi_cur);
}

int	init_philo_lst(int argc, char **argv, t_philo **phi_one, int start_time)
{
	t_philo	*phi_cur;
	t_philo	*phi_prev;
	int		phi_num;

	phi_num = 0;
	phi_prev = NULL;
	while (phi_num < ft_atoi(argv[1]))
	{
		phi_cur = ft_lstnew(phi_num + 1, start_time);
		if (phi_cur == NULL)
			return (write(2, "Init went wrong\n", 22),
				error_mutex_malloc_init(phi_prev), 1);
		phi_cur->gen_t_die = ft_atoi(argv[2]);
		phi_cur->gen_t_eat = ft_atoi(argv[3]);
		phi_cur->gen_t_sleep = ft_atoi(argv[4]);
		phi_cur->gen_num_eat = 2147483647;
		if (argc == 6)
			phi_cur->gen_num_eat = ft_atoi(argv[5]);
		ft_lstadd_back(phi_one, phi_cur);
		phi_prev = phi_cur;
		phi_num++;
	}
	(*phi_one)->prev = phi_cur;
	phi_cur->next = *phi_one;
	return (0);
}
