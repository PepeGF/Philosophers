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
	//	printf("Philo %d vivos(%d)hambre{%d}\n", ph->id, args->alive, ph->hungry);
		//pthread_mutex_lock(&args->mutex_satisfaction);//prescindible???
		pthread_mutex_lock(&args->mutex_life);
		if (args->alive == false || ph->hungry == false)
		{
			// write(1, "Huele a muerto\n", 15);
			pthread_mutex_unlock(&args->mutex_life);
		//	pthread_mutex_unlock(&args->mutex_satisfaction);//prescindible??
			break;
		}
		pthread_mutex_unlock(&args->mutex_life);
		//pthread_mutex_unlock(&args->mutex_satisfaction);
		if (ft_eating(ph))
			break;
		ft_sleeping(ph);
		ft_thinking(ph);
	}
	/*while (args->alive == true && args->hungry == true)
	{
		if (ft_eating(ph))
			break;
		 if (args->n_meal != 0 && ph->meals == args->n_meal)
		 	break;
		ft_sleeping(ph);
		ft_thinking(ph);
	}*/
	return (NULL);
}

int	ft_eating(t_philo *philo)
{
	pthread_mutex_lock(&philo->fork);
	ft_print("has taken a RIGHT fork", philo); //quitar right
	if (philo->args->n_philo == 1)
	{
		pthread_mutex_unlock(&philo->fork);
		return (1);
	}
	pthread_mutex_lock(&philo->left->fork);
	ft_print("has taken a LEFT fork", philo); //quitar left
	ft_print("is eating", philo);
	// printf("Philo %d has eaten %d times\n", philo->id, philo->meals);
	// pthread_mutex_lock(&philo->args->mutex_satisfaction);
	philo->last_meal = ft_get_timestamp();
	//philo->meals++;
	if (philo->meals >= philo->args->n_meal && philo->args->n_meal != -1)
	{
	//	printf("\033[31mCOMIIIIIIDAS %d\033[0m\n", philo->args->n_meal);
		philo->hungry = false;
	}
	// pthread_mutex_unlock(&philo->args->mutex_satisfaction);
	usleep(philo->args->t_eat * 500);
	while (1/*philo->args->alive*/)
	{
		// pthread_mutex_lock(&philo->args->mutex_life);
		if (philo->args->alive == false)
		{
			// pthread_mutex_unlock(&philo->args->mutex_life);
			break;
		}
		// pthread_mutex_unlock(&philo->args->mutex_life);
		if (ft_get_timestamp() - philo->last_meal >= philo->args->t_eat)
			break;
		usleep(500);
	}
	// pthread_mutex_lock(&philo->args->mutex_satisfaction);
	philo->meals++;
	if (philo->meals >= philo->args->n_meal && philo->args->n_meal != -1)
	{
	//	printf("\033[32mCOMIIIIIIDAS %d\033[0m\n", philo->args->n_meal);
		philo->hungry = false;
	}
	// pthread_mutex_unlock(&philo->args->mutex_satisfaction);
	pthread_mutex_unlock(&philo->left->fork);
	//ft_print("has dropped LEFT fork", philo);
	pthread_mutex_unlock(&philo->fork);
	//ft_print("has dropped LEFT fork", philo);
	return (0);
}

void	ft_sleeping(t_philo *philo)
{
	int start_sleep;

	start_sleep = ft_get_timestamp();

	ft_print("is sleeping", philo);
	while (1/*philo->args->alive*/)
	{
		// pthread_mutex_lock(&philo->args->mutex_life);
		if (philo->args->alive == false)
		{
			// pthread_mutex_unlock(&philo->args->mutex_life);
			break;
		}
		// pthread_mutex_unlock(&philo->args->mutex_life);
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
