#include "../inc/philo.h"

void	ft_print(char *msg, t_philo *philo)
{
	pthread_mutex_lock(&philo->args->mutex_args);
	if (philo->args->alive == true)
	{
		printf("%lld ms %d %s\n", ft_get_timestamp()
			- philo->args->zero_time, philo->id, msg);
	}
	pthread_mutex_unlock(&philo->args->mutex_args);
}

void	ft_keep_eating(t_philo *philo, int duration)
{
	while (philo->args->alive)
	{
		if (ft_get_timestamp() - philo->last_meal >= duration)
			break;
		usleep(300);
	}
}

int	ft_eating(t_philo *philo)
{
	pthread_mutex_lock(&philo->fork);
	ft_print("has taken a RIGHT fork", philo);
	pthread_mutex_lock(&philo->left->fork);
	ft_print("has taken a LEFT fork", philo);
	ft_print("is eating", philo);
	philo->last_meal = ft_get_timestamp();
	while (philo->args->alive)
	{
		if (ft_get_timestamp() - philo->last_meal >= philo->args->t_eat)
			break;
		usleep(300);
	}
	// ft_keep_eating(philo, philo->args->t_eat);
	pthread_mutex_unlock(&philo->left->fork);
	// ft_print("has dropped LEFT fork", philo);
	pthread_mutex_unlock(&philo->fork);
	// ft_print("has dropped RIGHT fork", philo);
	philo->meals++;
	return (0);
}

void	ft_sleeping(t_philo *philo)
{
	int start_sleep;

	start_sleep = ft_get_timestamp();
	ft_print("is sleeping", philo);
	while (philo->args->alive)
	{
		if (ft_get_timestamp() - start_sleep >= philo->args->t_sleep)
			break;
		// usleep(duration / 100);
		usleep(500);
	}
	return ;
}

void	ft_thinking(t_philo *philo)
{
(void)philo;
	ft_print("is thinking", philo);
	return ;
}
