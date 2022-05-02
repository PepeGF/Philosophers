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
	t_philo *ph;
	
	ph = (t_philo *)philo;
	if (ph->id % 2 == 0)
		usleep(ph->args->t_eat * 100000 * 1.1); //si no funciona dejar un valor fijo
	while (ph->args->alive == true && ph->args->hungry == true)
	{
		ft_eating(ph);
		ft_sleeping(ph);
		ft_thinking(ph);

		break;//para q no sea infinito mientras pruebo.
	}

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
		aux = aux->right;
		i++;
	}
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

int	main(int argc, char *argv[])
{
	t_args		*args;
	t_philo		*lst_philo;

atexit(leaks);
	args = malloc(sizeof(t_args));
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
	if (ft_create_threads(lst_philo, &routine))
		return (1);
	if (ft_join_threads(lst_philo, args))
		return (1);
	ft_destroy_mutex(lst_philo, args);
	ft_free_philos(lst_philo, args);
	//free(args); //ojo con estoooooooooooooooooo, hay que liberarlo en más sitios
	return (0);
}
