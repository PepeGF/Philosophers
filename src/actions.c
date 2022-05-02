#include "../inc/philo.h"

void	ft_print(char *msg, t_philo *philo)
{
	pthread_mutex_lock(&philo->args->mutex_args);
	if (philo->args->alive == true)
	{
		printf("%lld ms %d %s\n", (ft_get_timestamp()
			- philo->args->zero_time) / 1000, philo->id, msg);
	}
	pthread_mutex_unlock(&philo->args->mutex_args);
}

int	ft_eating(t_philo *philo)
{
	pthread_mutex_lock(&philo->fork);
	ft_print("has taken a fork", philo);
	pthread_mutex_lock(&philo->left->fork);
	ft_print("has taken a fork", philo);
	/*printf("%lld ms %d has taken a fork\n", (ft_get_timestamp()
			- philo->args->zero_time) / 1000, philo->r_fork_id);*/
	ft_print("is eating", philo);
	philo->last_meal = ft_get_timestamp();
/*	printf("%lld ms %d is eating\n", (philo->last_meal
			- philo->args->zero_time) / 1000, philo->id);*/
	while (philo->args->alive)
	{
		if (ft_get_timestamp() - philo->last_meal >= philo->args->t_eat)
			break;
		usleep(philo->args->t_eat / 10);
	}
	philo->meals++;
	pthread_mutex_unlock(&philo->fork);
	pthread_mutex_unlock(&philo->left->fork);
	return (0);
}

void	ft_sleeping(t_philo *philo)
{
(void)philo;
	return ;
}

void	ft_thinking(t_philo *philo)
{
(void)philo;
	return ;
}
