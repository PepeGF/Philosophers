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

typedef struct s_data
{
	struct s_args	*args;
	struct s_philo	*philo;
	struct s_fork	*fork;
}	t_data;

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
	struct s_philo	*next;
}	t_philo;

typedef struct s_fork
{
	int				id;
	struct s_fork	*next;
}	t_fork;

int	ft_atoi(const char *str);
int	atoi_args(char **argv, t_args *args);
int	arg_number_manage(int argc);

#endif
