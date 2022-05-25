#include "../inc/philo.h"

void	ft_print(char *msg, t_philo *philo)
{
	pthread_mutex_lock(&philo->args->mutex_print);
	int time = ft_get_timestamp();
	if (philo->args->alive == true)
	{
		printf("%d ms %d %s(%d){%d}[%d]\n", /*ft_get_timestamp()*/time
			- philo->args->zero_time, philo->id, msg, philo->meals+1, philo->hungry,time - philo->last_meal);
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
	if (ph->id % 2 == 0 || ph->id == args->n_philo)
		usleep(args->t_eat * 500); //si no funciona dejar un valor fijo
	while (1)
	{
		//pthread_mutex_lock(&args->mutex_life);
		if (args->alive == false || ph->hungry == false)
		{
		//	pthread_mutex_unlock(&args->mutex_life);
			break;
		}
		//pthread_mutex_unlock(&args->mutex_life);
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
	pthread_mutex_lock(&philo->args->mutex_life);
	ft_print("is eating", philo); //meter dentro del mutex???
	philo->last_meal = ft_get_timestamp();
	pthread_mutex_unlock(&philo->args->mutex_life);
	usleep(philo->args->t_eat * 500);
	ft_keep_eating(philo);
	philo->meals++;
	if (philo->meals >= philo->args->n_meal && philo->args->n_meal != -1)
	{
		pthread_mutex_lock(&philo->args->mutex_satisfaction);
		philo->args->satisfied++;
		pthread_mutex_unlock(&philo->args->mutex_satisfaction);
		philo->hungry = false;
	}
	pthread_mutex_unlock(&philo->fork);
	pthread_mutex_unlock(&philo->left->fork);
	return (0);
}

void	ft_sleeping(t_philo *philo)
{
	int start_sleep;

	start_sleep = ft_get_timestamp();

	ft_print("is sleeping", philo);
	usleep(philo->args->t_sleep * 500);
	while (1/*philo->args->alive*/)
	{
		if (ft_get_timestamp() - start_sleep >= philo->args->t_sleep)
			break;
		usleep(500);
	}
	return ;
}

