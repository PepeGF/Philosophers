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

void	ft_do_nothing(t_philo *philo, int duration)
{
	while (philo->args->alive)
	{
		if ((ft_get_timestamp() - philo->last_meal) / 1000 >= duration)
			break;
		// usleep(duration / 100);
		usleep(50);
	}
}

int	ft_eating(t_philo *philo)
{
	pthread_mutex_lock(&philo->fork);
	ft_print("has taken a RIGHT fork", philo);
	pthread_mutex_lock(&philo->left->fork);
	ft_print("has taken a LEFT fork", philo);
	/*printf("%lld ms %d has taken a fork\n", (ft_get_timestamp()
			- philo->args->zero_time) / 1000, philo->r_fork_id);*/
	ft_print("is eating", philo);
	philo->last_meal = ft_get_timestamp();
/*	printf("%lld ms %d is eating\n", (philo->last_meal
			- philo->args->zero_time) / 1000, philo->id);*/
	ft_do_nothing(philo, philo->args->t_eat);
	/*while (philo->args->alive)
	{
		if (ft_get_timestamp() - philo->last_meal >= philo->args->t_eat)
			break;
		usleep(philo->args->t_eat / 10);
	}*/
	philo->meals++;
	pthread_mutex_unlock(&philo->left->fork);
	pthread_mutex_unlock(&philo->fork);
	return (0);
}

void	ft_sleeping(t_philo *philo)
{
	ft_print("is sleeping", philo);
	usleep(philo->args->t_sleep*1000);
	return ;
}

void	ft_thinking(t_philo *philo)
{
(void)philo;
	usleep(10);
	return ;
}
