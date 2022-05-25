#include "../inc/philo.h"

/*
int	ft_lst_len(t_philo *lst_philo)
{
	t_philo	*aux;
	int		i;

	if (!lst_philo)
		return (0);
	i = 0;
	aux = lst_philo;
	while (aux)
	{
		aux = aux->right;
		i++;
	}
	printf("Longitud lista: %d\n", i);
	return (i);
}
*/

void	ft_check_satisfaction(t_philo *philo, t_args *args)
{
	int	i;

	i = 0;
	if (args->n_meal != -1)
	{
		while (1)
		{
			pthread_mutex_lock(&args->mutex_satisfaction);
			if (philo->meals >= args->n_meal || i < args->n_philo)
			{
				pthread_mutex_unlock(&args->mutex_satisfaction);
				break;
			}
			pthread_mutex_unlock(&args->mutex_satisfaction);
			i++;
			if (i == args->n_philo)
			{
				pthread_mutex_lock(&args->mutex_satisfaction);
				args->hungry = false;
				args->alive = false;
				pthread_mutex_unlock(&args->mutex_satisfaction);
			}
		}
	}

	/*while (args->n_meal != -1 && philo->meals >= args->n_meal
			&& i < args->n_philo)
	{
		// pthread_mutex_lock(&philo->args->mutex_print);
		i++;
		// printf("%i\n", i);
		// pthread_mutex_unlock(&philo->args->mutex_print);
	}
	if (i == args->n_philo)
	{
		pthread_mutex_lock(&philo->args->mutex_life);
		args->hungry = false;
		printf("------Ya no hay hambre en el mundo------\n");
		pthread_mutex_unlock(&philo->args->mutex_life);	
	}*/
}

void	ft_check_death(t_philo *philo, t_args *args)
{
	t_philo	*aux;
	int		time;

	aux = philo;
	while (1/*args->alive*/)
	{
		//pthread_mutex_lock(&args->mutex_life);
		if (args->alive == false)
		{
			// pthread_mutex_unlock(&args->mutex_life);
			break;
		}
		// pthread_mutex_unlock(&args->mutex_life);
		// pthread_mutex_lock(&args->mutex_satisfaction);
		time = ft_get_timestamp() - aux->last_meal;
		// printf("Philo %d - time last_meal: %d\n", aux->id, time);
		// pthread_mutex_unlock(&args->mutex_satisfaction);
		if (time > args->t_die && args->alive == true)
		{
			ft_print("is dead", aux);
			pthread_mutex_lock(&args->mutex_life);
			args->alive = false;
			pthread_mutex_unlock(&args->mutex_life);
		}
		//printf("Philo :%d Dirección: %p\n", aux->id, &aux->last_meal);
		//printf("Philo %d -> tiempo: %d -> muerte: %d -> Vivos: %d -> Hambre: %d\n", aux->id, time, args->t_die, args->alive, args->hungry);
		ft_check_satisfaction(aux, args);
		if (!args->hungry)
			break;
		aux = aux->right;
		usleep(500);
	}
}

int	ft_check_death_1(t_philo *philo, t_args *args)
{
	int	time;

	//pthread_mutex_lock(&args->mutex_satisfaction);
	time = ft_get_timestamp() - philo->last_meal;
	//pthread_mutex_unlock(&args->mutex_satisfaction);
	if (time > args->t_die)
	{
		pthread_mutex_lock(&args->mutex_life);
		printf("time %d ms %d is dead\n", time, philo->id);
		args->alive = false;
		args->hungry = false;
		pthread_mutex_unlock(&args->mutex_life);
		return (1);
	}
	return (0);
}

int	ft_check_satisfaction_1(t_philo *philo, t_args *args)
{
(void)args;
	//si ha comido suficiente devolver 1
	// pthread_mutex_lock(&args->mutex_satisfaction);
	if (!philo->hungry)
	{
		// pthread_mutex_unlock(&args->mutex_satisfaction);
		return (1);
	}
	// pthread_mutex_unlock(&args->mutex_satisfaction);
	//si no ha comido suficiente devolver 0
	return (0);
}

void	ft_check_status(t_philo *philo, t_args *args)
{
	t_philo	*aux;
	int		hungry_philos;

	aux = philo;
	hungry_philos = args->n_philo;
	while (1)
	{
		if (ft_check_death_1(aux, args))
			break;
		if (args->n_meal != -1)
		{
			if (ft_check_satisfaction_1(aux, args))
				hungry_philos--;
			else
				hungry_philos = args->n_philo;
		}
		if (hungry_philos <= 0)
		{
			pthread_mutex_lock(&args->mutex_satisfaction);
			args->hungry = false;
			// printf("%s\n", "------Ya no hay hambre en el mundo------");
			pthread_mutex_unlock(&args->mutex_satisfaction);
			break;
		}
		aux = aux->right;
		usleep(8000 / args->n_philo);
	}
}

void ft_prueba()
{
	struct timeval time1;
	struct timeval time2;

	gettimeofday(&time1, NULL);
	usleep(1000);
	gettimeofday(&time2, NULL);

	long long wololo1 = time1.tv_sec * 1000000 + time1.tv_usec;
	long long wololo2 = time2.tv_sec * 1000000 + time2.tv_usec;
	printf("tiempo en 1000 us: %llu, porcentaje %.2lld \n", wololo2 - wololo1, (wololo2 - wololo1)*100/1000-100);

	gettimeofday(&time1, NULL);
	usleep(500);
	gettimeofday(&time2, NULL);

	wololo1 = time1.tv_sec * 1000000 + time1.tv_usec;
	wololo2 = time2.tv_sec * 1000000 + time2.tv_usec;
	printf("tiempo en 500 us: %llu, porcentaje %.2lld \n", wololo2 - wololo1, (wololo2 - wololo1)*100/500-100);

	gettimeofday(&time1, NULL);
	usleep(300);
	gettimeofday(&time2, NULL);

	wololo1 = time1.tv_sec * 1000000 + time1.tv_usec;
	wololo2 = time2.tv_sec * 1000000 + time2.tv_usec;
	printf("tiempo en 300 us: %llu, porcentaje %.2lld \n", wololo2 - wololo1, (wololo2 - wololo1)*100/300-100);

	gettimeofday(&time1, NULL);
	usleep(200);
	gettimeofday(&time2, NULL);

	wololo1 = time1.tv_sec * 1000000 + time1.tv_usec;
	wololo2 = time2.tv_sec * 1000000 + time2.tv_usec;
	printf("tiempo en 200 us: %llu, porcentaje %.2lld \n", wololo2 - wololo1, (wololo2 - wololo1)*100/200-100);

	gettimeofday(&time1, NULL);
	usleep(100);
	gettimeofday(&time2, NULL);

	wololo1 = time1.tv_sec * 1000000 + time1.tv_usec;
	wololo2 = time2.tv_sec * 1000000 + time2.tv_usec;
	printf("tiempo en 100 us: %llu, porcentaje %.2lld \n", wololo2 - wololo1, (wololo2 - wololo1)*100/100-100);
}