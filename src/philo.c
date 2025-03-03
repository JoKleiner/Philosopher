/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joklein <joklein@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/28 11:26:15 by joklein           #+#    #+#             */
/*   Updated: 2025/03/03 13:10:35 by joklein          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_input(char **argv)
{
	int	num;
	int	i;

	i = 1;
	while (argv[i])
	{
		num = ft_atoi(argv[i]);
		if (num <= 0)
			return (write(1, "Wrong input\n", 12), 1);
		if (i == 1 && num > 200)
			return (write(1, "Too many philosophers\n", 22), 1);
		if (i != 1 && i != 5 && num < 60)
			return (write(1, "All times must be longer than 60ms\n", 35), 1);
		i++;
	}
	return (0);
}

int	check_arg(int argc, char **argv)
{
	int	i;
	int	u;

	if (argc == 1)
	{
		write(1, "num phi\ndie time\neat time\nsleep time\nnum must eat\n", 50);
		return (1);
	}
	if (argc != 5 && argc != 6)
		return (write(1, "Num of arg incorrect\n", 21), 1);
	i = 1;
	while (argv[i])
	{
		u = 0;
		while (argv[i][u])
		{
			if (argv[i][u] < '0' || argv[i][u] > '9')
				return (write(1, "Arg incorrect\n", 14), 1);
			u++;
		}
		i++;
	}
	if (check_input(argv) == 1)
		return (1);
	return (0);
}

int	main(int argc, char **argv)
{
	t_philo			*phi_one;
	struct timeval	tv;
	int				start_time;

	if (check_arg(argc, argv) == 1)
		return (1);
	gettimeofday(&tv, NULL);
	start_time = tv.tv_sec * 1000 + (tv.tv_usec / 1000);
	phi_one = NULL;
	if (init_philo_lst(argc, argv, &phi_one, start_time) == 1)
		return (1);
	if (create_phi_thread(argv, phi_one) == 1)
		return (ft_lstclear(&phi_one), 1);
	if (create_moni_thread(phi_one) == 1)
		return (join_philo_thread(phi_one), ft_lstclear(&phi_one), 1);
	write_end(phi_one);
	join_philo_thread(phi_one);
	ft_lstclear(&phi_one);
	return (0);
}

// void	c(void)
// {
// 	system("leaks philo");
// }

// atexit(c);
