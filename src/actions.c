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
		usleep(1000); //si no funciona dejar un valor fijo
	while (args->alive == true)
	{
		if (args->n_meal != 0 && ph->meals == args->n_meal)
			break;
		ft_eating(ph);
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
	ft_print("is eating", philo);
	pthread_mutex_lock(&philo->args->mutex_print);
	philo->last_meal = ft_get_timestamp();
	printf("--Philo: %d Dirección: %p\n", philo->id, &philo->last_meal);
	pthread_mutex_unlock(&philo->args->mutex_print);
	while (philo->args->alive)
	{
		if (ft_get_timestamp() - philo->last_meal >= philo->args->t_eat)
			break;
		usleep(300);
	}
	pthread_mutex_unlock(&philo->left->fork);
	pthread_mutex_unlock(&philo->fork);
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
