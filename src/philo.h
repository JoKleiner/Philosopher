/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joklein <joklein@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/28 11:26:13 by joklein           #+#    #+#             */
/*   Updated: 2025/05/28 15:08:49 by joklein          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

typedef enum e_status
{
	not_eat,
	eat,
	dead,
	full
}					t_status;

typedef struct s_philo
{
	struct s_philo	*prev;
	struct s_philo	*next;
	int				num;
	int				times_eaten;
	int				last_meal;
	int				t_start;
	t_status		eating;
	t_status		status;
	int				gen_t_die;
	int				gen_t_eat;
	int				gen_t_sleep;
	int				gen_num_eat;
	pthread_mutex_t	fork;
	pthread_mutex_t	print;
	pthread_mutex_t	block;
	pthread_t		threads;
}					t_philo;

typedef struct s_monitor
{
	pthread_t		threads;
}					t_monitor;

// main
int					main(int argc, char **argv);
int					check_arg(int argc, char **argv);
int					check_input(char **argv);

// list
int					init_philo_lst(int argc, char **argv, t_philo **phi_one,
						int start_time);
t_philo				*ft_lstnew(int content, int start_time);
void				ft_lstadd_back(t_philo **lst, t_philo *new);
t_philo				*ft_lstlast(t_philo *lst);
void				ft_lstclear(t_philo **lst);

// philo_thread
int					create_phi_thread(char **argv, t_philo *phi_cur);
void				*philo_thread(void *philo);
int					lock_fork(t_philo *phi_cur, t_philo *phi_prev);
int					unlock_fork(t_philo *phi_cur, t_philo *phi_prev);

// monitor_thread
int					create_moni_thread(t_philo *phi_cur);
void				*monitor_thread(void *philo);
int					set_dead(t_philo *phi_cur, t_philo *phi_one);
void				set_all_dead(t_philo *phi_cur);

// thread_end
int					set_full(t_philo *phi_cur);
void				set_all_full(t_philo *phi_cur);
int					end_quest(t_philo *phi_cur);
void				join_philo_thread(t_philo *phi);
void				detach_philo_thread(t_philo *phi);

// utils
int					ft_atoi(const char *str);
void				init_wait(t_philo *phi_cur);
int					mysleep(int wait_time, t_philo *phi_cur);
void				error_mutex_malloc_init(t_philo *phi_cur);

// utils_write
int					write_stamp(char *text, t_philo *philo);
int					write_fork_eat(t_philo *philo);
void				write_end(t_philo *philo);

#endif
