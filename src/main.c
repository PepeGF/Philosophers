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

void	ft_create_mutex(t_philo *lst_philo, t_args *args)
{
	int		i;
	t_philo	*aux;
//hay que gestionar la liberación y el cierre si la creación de los mutex fallan

	i = 1;
	aux = lst_philo;
	if (pthread_mutex_init(&args->mutex_args, NULL))
	printf("Problema creando el mutex de args nº\n");
	while (i <= args->n_philo)
	{
		if (pthread_mutex_init(&aux->fork, NULL))
			printf("Problema creando el mutex fork nº %d\n", aux->id);
		// if (pthread_mutex_init(&aux->mutex2, NULL))
		// 	printf("Problema creando el mutex mutex2 nº %d\n", aux->id);
		aux = aux->right;
		i++;
	}
}

void	ft_destroy_mutex(t_philo *lst_philo, t_args *args)
{
	int		i;
//hay que gestionar la liberación y el cierre si los destroy de los mutex fallan
	i = 1;
	if (pthread_mutex_destroy(&args->mutex_args))
			printf("Problema destruyendo el mutex de args\n");
	while (i <= args->n_philo)
	{
		if (pthread_mutex_destroy(&lst_philo->fork))
			printf("Problema destruyendo el mutex fork nº %d\n", lst_philo->id);
		// if (pthread_mutex_destroy(&lst_philo->mutex2))
		// 	printf("Problema destruyendo el mutex mutex2 nº %d\n", lst_philo->id);
		
		lst_philo = lst_philo->right;
		i++;
	}
}

void	ft_check_death(t_philo *philo, t_args *args)
{
	t_philo	*aux;

	aux = philo;
	while (args->alive && args->hungry)
	{
		pthread_mutex_lock(&args->mutex_args);
		if ((ft_get_timestamp() - aux->last_meal) / 1000 > args->t_die)
		{
			args->alive = false;
			ft_print("is dead", aux);
		}
		pthread_mutex_unlock(&args->mutex_args);
		aux = philo->right;
		break ;
	}
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
	ft_create_mutex(lst_philo, args);
	
	args->zero_time = ft_get_timestamp();
	if (ft_create_threads(lst_philo, &routine))
		return (1);
	ft_check_death(lst_philo, args);
	if (ft_join_threads(lst_philo, args))
		return (1);
	ft_destroy_mutex(lst_philo, args);
	ft_free_philos(lst_philo, args);
	//free(args); //ojo con estoooooooooooooooooo, hay que liberarlo en más sitios
	return (0);
}
