/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josgarci <josgarci@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/22 17:15:57 by josgarci          #+#    #+#             */
/*   Updated: 2022/05/07 12:42:47 by josgarci         ###   ########.fr       */
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
	while (args->n_meal != -1 && philo->meals >= args->n_meal
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
	}
}

void	ft_check_death(t_philo *philo, t_args *args)
{
	t_philo	*aux;
	int		time;

	aux = philo;
	while (args->alive)
	{
		pthread_mutex_lock(&args->mutex_life);
		time = ft_get_timestamp() - aux->last_meal;
		// printf("Philo %d - time last_meal: %d\n", aux->id, time);
		if (time > args->t_die)
		{
			ft_print("is dead", aux);
			args->alive = false;
		}
		pthread_mutex_unlock(&args->mutex_life);
		//printf("Philo :%d Dirección: %p\n", aux->id, &aux->last_meal);
		//printf("Philo %d -> tiempo: %d -> muerte: %d -> Vivos: %d -> Hambre: %d\n", aux->id, time, args->t_die, args->alive, args->hungry);
		ft_check_satisfaction(aux, args);
		if (!args->hungry)
			break;
		aux = aux->right;
		usleep(500);
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
