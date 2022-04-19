#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdio.h>

typedef struct s_args
{
	int	n_philo;
	int	t_die;
	int	t_eat;
	int	t_sleep;
	int	n_meal;
} t_args;

int	ft_atoi(const char *str);

#endif
