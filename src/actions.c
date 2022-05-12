#include "../inc/philo.h"

void	*routine(void *philo)
{
	t_philo *ph;
	t_args	*args;
	
	ph = (t_philo *)philo;
	args = ph->args;
	// printf("tiempo espera ->%f\n", args->t_eat * 1.1);
	if (ph->id % 2 == 0)
		usleep(args->t_eat * 1100); //si no funciona dejar un valor fijo
	while (args->alive == true/*args->hungry == true*/)
	{
		if (args->n_meal != 0 && ph->meals == args->n_meal)
			break ;
		ft_eating(ph);
		ft_sleeping(ph);
		ft_thinking(ph);
		// break;//para q no sea infinito mientras pruebo.
	}
	return (NULL);
}

void	ft_print(char *msg, t_philo *philo)
{
	pthread_mutex_lock(&philo->args->mutex_print);
	if (philo->args->alive == true)
	{
		printf("%lld ms %d %s\n", (ft_get_timestamp()
			- philo->args->zero_time) / 1000, philo->id, msg);
	}
	pthread_mutex_unlock(&philo->args->mutex_print);
}

void	ft_keep_eating(t_philo *philo, int duration)
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
	ft_print("has taken a fork", philo);
	pthread_mutex_lock(&philo->left->fork);
	ft_print("has taken a fork", philo);
	ft_print("is eating", philo);
	philo->last_meal = ft_get_timestamp();
	philo->meals++;
	ft_keep_eating(philo, philo->args->t_eat);
	pthread_mutex_unlock(&philo->left->fork);
	pthread_mutex_unlock(&philo->fork);
	return (0);
}

void	ft_sleeping(t_philo *philo)
{
	long long	start;

	start = ft_get_timestamp();
	ft_print("is sleeping", philo);
	while (philo->args->alive)
	{
		if ((ft_get_timestamp() - start) / 1000 >= philo->args->t_sleep)
			break;
		usleep(50);
	}
	// ft_keep_doing(philo, philo->args->t_sleep);
	return ;
}

void	ft_thinking(t_philo *philo)
{
	ft_print("is thinking", philo);
	return ;
}
