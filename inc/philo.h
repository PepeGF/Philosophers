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

typedef enum status
{
	ALIVE,
	DEAD,
	EATING,
	SLEEPING,
	THINKING
}	t_status;

typedef struct s_args
{
	int	n_philo;
	int	t_die;
	int	t_eat;
	int	t_sleep;
	int	n_meal;
}	t_args;

typedef struct s_philo
{
	int				id;
	pthread_t		thread;
	int				fork_id;
	int				status;
	pthread_mutex_t	fork;
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

/* List functions */
t_philo	*ft_lstnew(int id);
void	ft_lstadd_back(t_philo **lst, t_philo *new);
t_philo	*ft_lstlast(t_philo *lst);

/* Lists functions */
t_philo	*ft_lstlast(t_philo *lst);
void	ft_lstadd_back(t_philo **lst, t_philo *new);
t_philo	*ft_lstnew(int id);
void	ft_link_list(t_philo *lst_philo);

/* Philos functions */
void	ft_create_philos(t_philo **lst_philo, t_args args);
void	ft_init_philos(t_philo	*lst_philo, t_args args);
void	ft_free_philos(t_philo *lst_philo, t_args args);

/* Threads functions */
int		ft_create_threads(t_philo *lst_philo, void *routine);
int		ft_join_threads(t_philo *lst_philo, t_args args);

#endif
