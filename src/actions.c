#include "../inc/philo.h"

void	ft_print(char *msg, t_philo *philo)
{
	pthread_mutex_lock(&philo->args->mutex_print);
	if (philo->args->alive == true)
	{
		printf("%d ms %d %s\n", ft_get_timestamp()
			- philo->args->zero_time, philo->id, msg);
	}
	pthread_mutex_unlock(&philo->args->mutex_print);
}

void	*routine(void *philo)
{
	t_philo *ph;
	t_args	*args;
	
	ph = (t_philo *)philo;
	args = ph->args;
	ph->last_meal = ft_get_timestamp();
	if (ph->id % 2 == 0)
		usleep(args->t_eat * 0.9); //si no funciona dejar un valor fijo
	while (args->alive == true && args->hungry == true)
	{
		if (ft_eating(ph))
			break;
		 if (args->n_meal != 0 && ph->meals == args->n_meal)
		 	break;
		ft_sleeping(ph);
		ft_thinking(ph);
	}
	return (NULL);
}

int	ft_eating(t_philo *philo)
{
	pthread_mutex_lock(&philo->fork);
	ft_print("has taken a RIGHT fork", philo);
	if (philo->args->n_philo == 1)
	{
		pthread_mutex_unlock(&philo->fork);
		return (1);
	}
	pthread_mutex_lock(&philo->left->fork);
	ft_print("has taken a LEFT fork", philo);
	pthread_mutex_lock(&philo->args->mutex_life);
	ft_print("is eating", philo);
	// printf("Philo %d has eaten %d times\n", philo->id, philo->meals);
	philo->last_meal = ft_get_timestamp();
	pthread_mutex_unlock(&philo->args->mutex_life);
	while (philo->args->alive)
	{
		if (ft_get_timestamp() - philo->last_meal >= philo->args->t_eat)
			break;
		usleep(300);
	}
	philo->meals++;
	pthread_mutex_unlock(&philo->left->fork);
	pthread_mutex_unlock(&philo->fork);
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
		usleep(300);
	}
	return ;
}

void	ft_thinking(t_philo *philo)
{
	ft_print("is thinking", philo);
	return ;
}
