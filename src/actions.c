#include "../inc/philo.h"

void	ft_print(char *msg, t_philo *philo)
{
	pthread_mutex_lock(&philo->args->mutex_life);
	int time = ft_get_timestamp();
	if (philo->args->alive == true)
	{
		printf("%d ms %d %s(%d){%d}[%d]\n", /*ft_get_timestamp()*/time
			- philo->args->zero_time, philo->id, msg, philo->meals+1, philo->hungry,time - philo->last_meal);
	}
	pthread_mutex_unlock(&philo->args->mutex_life);
}

void	*routine(void *philo)
{
	t_philo *ph;
	t_args	*args;
	
	ph = (t_philo *)philo;
	args = ph->args;
	ph->last_meal = ft_get_timestamp();
	if (ph->id % 2 == 0)
		usleep(args->t_eat * 500); //si no funciona dejar un valor fijo
	while (1)
	{
		pthread_mutex_lock(&args->mutex_life);
		if (args->alive == false || ph->hungry == false)
		{
			pthread_mutex_unlock(&args->mutex_life);
			break;
		}
		pthread_mutex_unlock(&args->mutex_life);
		if (ft_eating(ph))
			break;
		ft_sleeping(ph);
		ft_print("is thinking", ph);
	}
	return (NULL);
}

void	ft_keep_eating(t_philo *philo)
{
	while (1/*philo->args->alive*/)
	{
		if (philo->args->alive == false)
			break;
		if (ft_get_timestamp() - philo->last_meal >= philo->args->t_eat)
			break;
		usleep(500);
	}
}

int	ft_eating(t_philo *philo)
{
	pthread_mutex_lock(&philo->fork);
	ft_print("has taken a fork (right)", philo); //quitar right
	if (philo->args->n_philo == 1)
	{
		pthread_mutex_unlock(&philo->fork);
		return (1);
	}
	pthread_mutex_lock(&philo->left->fork);
	ft_print("has taken a fork (left)", philo); //quitar left
	ft_print("is eating", philo);
	philo->last_meal = ft_get_timestamp();
	if (philo->meals >= philo->args->n_meal && philo->args->n_meal != -1)
		philo->hungry = false;
	usleep(philo->args->t_eat * 500);
	ft_keep_eating(philo);
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
	while (1/*philo->args->alive*/)
	{
		if (ft_get_timestamp() - start_sleep >= philo->args->t_sleep)
			break;
		usleep(500);
	}
	return ;
}

void	ft_thinking(t_philo *philo)
{
	ft_print("is thinking", philo);
	return ;
	//esta función se podría quitar
}
