/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josgarci <josgarci@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/22 17:15:57 by josgarci          #+#    #+#             */
/*   Updated: 2022/04/22 18:25:11 by josgarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	leaks()
{
	system("leaks philo");
}

void	*routine(void *philo)
{
	// t_philo *ph;
	
	// ph = (t_philo *)philo;
	printf("ZZZZZero time in routine: %llu\n", ((t_philo *)philo)->args->zero_time);
	if (((t_philo *)philo)->id % 2 == 0)
		usleep(((t_philo *)philo)->args->t_eat * 100000 * 1.1); //si no funciona dejar un valor fijo
	while (((t_philo *)philo)->args->alive == true && ((t_philo *)philo)->args->hungry == true)
	{
		ft_eating((t_philo *)philo);
		ft_sleeping((t_philo *)philo);
		ft_thinking((t_philo *)philo);

		break;//para q no sea infinito mientras pruebo.
	}


/*	int	start;
	int	end;
	int	elapsed;
	struct timeval	moment;

	gettimeofday(&moment, NULL);
	start = moment.tv_sec * 1000000 + moment.tv_usec;
	printf("%i - %i\n", start, INT_MAX); 
	usleep(1 / ((t_philo *)philo)->id);
	// printf("\033[36m%p\033[0m\n", ((t_philo *)philo)->args);
	printf("filó nº %d, el tenedorD es %d, tenedorI es %d\n", ((t_philo *)philo)->id, ((t_philo *)philo)->r_fork_id, ((t_philo *)philo)->l_fork_id);
	printf("En total semos: %d pensadores\n", ((t_philo *)philo)->args->n_philo);
	gettimeofday(&moment, NULL);
	end = moment.tv_sec * 1000000 + moment.tv_usec;
	elapsed = end - start;
	printf("Soy el \033[7;32m%d\033[0m, he tardado\033[31m %d\033[0m\n", ((t_philo *)philo)->id, elapsed);
*/
	/*// printf("%d\n", start);
	usleep(1500000);
	gettimeofday(&moment, NULL);
	end = moment.tv_sec * 1000000 + moment.tv_usec;
	// printf("%d\n", end);
	elapsed = end - start;
	printf("%d\n", elapsed);*/
	return (NULL);
}

void	ft_create_mutex(t_philo *lst_philo, t_args *args)
{
	int		i;
	t_philo	*aux;
//hay que gestionar la liberación y el cierre si la creación de los mutex fallan

	i = 1;
	aux = lst_philo;
	while (i <= args->n_philo)
	{
		if (pthread_mutex_init(&aux->fork, NULL))
			printf("Problema creando el mutex fork nº %d\n", aux->id);
		if (pthread_mutex_init(&aux->mutex2, NULL))
			printf("Problema creando el mutex mutex2 nº %d\n", aux->id);
		if (pthread_mutex_init(&aux->mutex3, NULL))
			printf("Problema creando el mutex mutex nº %d\n", aux->id);

/*		if (aux->id % 2 != 0)
			pthread_mutex_lock(&aux->fork);
		else
			pthread_mutex_unlock(&aux->fork);*/
		aux = aux->right;
		i++;
	}
/*	i = 1;
	aux = lst_philo;
	while (i <= args->n_philo)
	{

		aux = aux->right;
		i++;
	}*/
}

void	ft_destroy_mutex(t_philo *lst_philo, t_args *args)
{
	int		i;
//hay que gestionar la liberación y el cierre si los destroy de los mutex fallan
	i = 1;
	while (i <= args->n_philo)
	{
		if (pthread_mutex_destroy(&lst_philo->fork))
			printf("Problema destruyendo el mutex fork nº %d\n", lst_philo->id);
		if (pthread_mutex_destroy(&lst_philo->mutex2))
			printf("Problema destruyendo el mutex mutex2 nº %d\n", lst_philo->id);
		if (pthread_mutex_destroy(&lst_philo->mutex3))
			printf("Problema destruyendo el mutex mutex3 nº %d\n", lst_philo->id);
		lst_philo = lst_philo->right;
		i++;
	}
}

/*t_data	*ft_init_data(t_philo *lst_philo, t_args *args)
{
	t_data *data;

	data = malloc (sizeof(t_data *));
	data->args = args;
	data->lst_philo = lst_philo;
	return (data);
}*/

void	verify_zero_time(t_philo *lst_philo)
{
	int i = 1;

	while (i <= lst_philo->args->n_philo)
	{
		printf("Filo nº %d, tiempo_zero: %llu\n", lst_philo->id, lst_philo->args->zero_time);
		lst_philo = lst_philo->right;
		i++;
	}
}

int	main(int argc, char *argv[])
{
	t_args		*args;
	t_philo		*lst_philo;

atexit(leaks);
	args = malloc(sizeof(t_args *));
	if (!args)
		return (1);
	if (!arg_number_manage(argc) || atoi_args(argv, args))
		return (1);
	lst_philo = 0;
	ft_create_philos(&lst_philo, args);
	ft_link_list(lst_philo);
	ft_init_philos(lst_philo, args);
	ft_create_mutex(lst_philo, args);
	
	args->zero_time = ft_get_timestamp();
	printf("Tiempo zero main: %llu\n", args->zero_time);
	verify_zero_time(lst_philo);
	if (ft_create_threads(lst_philo, &routine))
		return (1);
	if (ft_join_threads(lst_philo, args))
		return (1);
	ft_destroy_mutex(lst_philo, args);
	ft_free_philos(lst_philo, args);
	//free(args); //ojo con estoooooooooooooooooo, hay que liberarlo en más sitios
	return (0);
}
