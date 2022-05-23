/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josgarci <josgarci@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/22 17:15:57 by josgarci          #+#    #+#             */
/*   Updated: 2022/05/23 19:02:15 by josgarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	leaks()
{
	system("leaks philo");
}

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
		pthread_mutex_lock(&args->mutex_life);
		if (args->alive == false)
		{
			pthread_mutex_unlock(&args->mutex_life);
			break;
		}
		pthread_mutex_unlock(&args->mutex_life);
		pthread_mutex_lock(&args->mutex_satisfaction);
		time = ft_get_timestamp() - aux->last_meal;
		// printf("Philo %d - time last_meal: %d\n", aux->id, time);
		pthread_mutex_unlock(&args->mutex_satisfaction);
		if (time > args->t_die)
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

	pthread_mutex_lock(&args->mutex_satisfaction);
	time = ft_get_timestamp() - philo->last_meal;
	pthread_mutex_unlock(&args->mutex_satisfaction);
	if (time > args->t_die)
	{
		pthread_mutex_lock(&args->mutex_life);
		printf("%d is dead // time = %d\n", philo->id, time);
		args->alive = false;
		pthread_mutex_unlock(&args->mutex_life);
		return (1);
	}
	return (0);
}

int	ft_check_satisfaction_1(t_philo *philo, t_args *args)
{
	//si ha comido suficiente devolver 1
	pthread_mutex_lock(&args->mutex_satisfaction);
	if (!philo->hungry)
	{
		pthread_mutex_unlock(&args->mutex_satisfaction);
		return (1);
	}
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
			pthread_mutex_unlock(&args->mutex_satisfaction);
			break;
		}
		aux = aux->right;
		usleep(9000 / args->n_philo);
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

int	main(int argc, char *argv[])
{
	t_args		*args;
	t_philo		*lst_philo;

 // atexit(leaks);
	args = malloc(sizeof(t_args));
	if (!args)
		return (1);
	if (!arg_number_manage(argc) || atoi_args(argv, args))
		return (1);
	lst_philo = 0;
	ft_create_philos(&lst_philo, args);
	ft_link_list(lst_philo);
	ft_init_philos(lst_philo, args);
//ft_prueba();
	
	ft_create_mutex(lst_philo, args);
	args->zero_time = ft_get_timestamp();
	if (ft_create_threads(lst_philo, &routine))
		return (1);
	ft_check_status(lst_philo, args);
	//ft_check_death(lst_philo, args);
	if (ft_join_threads(lst_philo, args))
		return (1);
	ft_destroy_mutex(lst_philo, args);
	
	ft_free_philos(lst_philo, args);
	//free(args); //ojo con estoooooooooooooooooo, hay que liberarlo en más sitios
	return (0);
}
