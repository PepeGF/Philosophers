/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josgarci <josgarci@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/22 17:14:37 by josgarci          #+#    #+#             */
/*   Updated: 2022/04/22 17:28:33 by josgarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>
# include <stdbool.h>
# include <limits.h>

/*typedef enum status
{
	ALIVE,
	DEAD,
	EATING,
	SLEEPING,
	THINKING
}	t_status;*/

typedef struct s_args
{
	int				n_philo;
	int				t_die;
	int				t_eat;
	int				t_sleep;
	int				n_meal;
	bool			alive;
	bool			hungry;
	long long		zero_time;
	pthread_mutex_t	mutex_args;
}	t_args;

typedef struct s_philo
{
	int				id;
	pthread_t		thread;
	int				meals;
	int				r_fork_id;
	int				l_fork_id;
	long long		last_meal;
	pthread_mutex_t	fork;
	pthread_mutex_t	mutex2;
	struct s_philo	*right;
	struct s_philo	*left;
	struct timeval	start;
	struct timeval	end;
	struct timeval	current;
	struct s_args	*args;
}	t_philo;

/*
struct timeval
{
	time_t		tv_sec;
	suseconds_t	tv_usec;
};
*/

/* Arguments manage */
int		ft_atoi(const char *str);
int		atoi_args(char **argv, t_args *args);
int		arg_number_manage(int argc);

/* Lists functions */
t_philo	*ft_lstlast(t_philo *lst);
void	ft_lstadd_back(t_philo **lst, t_philo *new);
t_philo	*ft_lstnew(int id);
void	ft_link_list(t_philo *lst_philo);

/* Philos functions */
void	ft_create_philos(t_philo **lst_philo, t_args *args);
void	ft_init_philos(t_philo	*lst_philo, t_args *args);
void	ft_free_philos(t_philo *lst_philo, t_args *args);

/* Threads functions */
int		ft_create_threads(t_philo *lst_philo, void *routine);
int		ft_join_threads(t_philo *lst_philo, t_args *args);

/* Action functions */
void	*routine(void *philo);
int		ft_eating(t_philo *philo);
void	ft_sleeping(t_philo *philo);
void	ft_thinking(t_philo *philo);

/* Time functions */
long long	ft_get_timestamp(void);
//void	ft_set_zero_time(t_args *args);

#endif
