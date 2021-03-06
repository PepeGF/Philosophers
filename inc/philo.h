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

typedef struct s_args
{
	int				n_philo;
	int				t_die;
	int				t_eat;
	int				t_sleep;
	int				n_meal;
	bool			alive;
	bool			hungry;
	int				zero_time;
	int				satisfied;
	pthread_mutex_t	mutex_life;
	pthread_mutex_t	mutex_satisfaction;
	pthread_mutex_t	mutex_print;
}	t_args;

typedef struct s_philo
{
	int				id;
	pthread_t		thread;
	int				meals;
	int				last_meal;
	bool			hungry;
	pthread_mutex_t	fork;
	struct s_philo	*right;
	struct s_philo	*left;
	struct s_args	*args;
}	t_philo;

/* Main file */
int		ft_first_part(int argc, char *argv[], t_philo **lst_philo,
			t_args *args);
int		ft_second_part(t_philo *lst_philo, t_args *args);

/* Arguments manage */
int		atoi_args(char **argv, t_args *args);
int		arg_number_manage(int argc, t_args *args);
void	ft_fill_args(t_args *args, int *matrix, char **argv);

/* Lists functions */
t_philo	*ft_lstlast(t_philo *lst);
void	ft_lstadd_back(t_philo **lst, t_philo *new);
t_philo	*ft_lstnew(int id);
void	ft_link_list(t_philo *lst_philo);

/* Philos functions */
int		ft_create_philos(t_philo **lst_philo, t_args *args);
void	ft_init_philos(t_philo	*lst_philo, t_args *args);
void	ft_free_philos(t_philo *lst_philo, t_args *args);

/* Threads functions */
int		ft_create_threads(t_philo *lst_philo, void *routine);
int		ft_join_threads(t_philo *lst_philo, t_args *args);
int		ft_create_mutex(t_philo *lst_philo, t_args *args);
int		ft_destroy_mutex(t_philo *lst_philo, t_args *args);

/* Action functions */
void	ft_print(char *msg, t_philo *philo);
void	*ft_routine(void *philo);
int		ft_eating(t_philo *philo);
void	ft_keep_eating(t_philo *philo);
void	ft_sleeping(t_philo *philo);

/* Time functions */
int		ft_get_timestamp(void);
void	ft_set_zero_time(t_args *args);

/* Checker functions */
int		ft_check_satisfaction(t_philo *philo, t_args *args);
void	ft_check_status(t_philo *philo, t_args *args);

/* Atoi function */
int		ft_atoi(const char *str);

#endif
