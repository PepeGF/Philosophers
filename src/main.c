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

void	ft_check_status(t_philo *lst_philo, t_args *args)
{
	t_philo	*aux;
	int		i;

	aux = lst_philo;
	i = 0;
	while (args->alive)
	{
		if (aux->meals == args->n_meal)
			i++;
		if (args->alive == false)
			break ;
		if (i == args->n_philo)
			break ;
		aux = aux->right;
		if (aux == lst_philo)
			i = 0;
	}
}

void	ft_check_death(t_philo *philo, t_args *args)
{
	t_philo	*aux;
int i = 0;
	aux = philo;
	while (args->alive && args->hungry && i < 200)
	{
		if (!pthread_mutex_lock(&args->mutex_args))
			printf("\n%s\n\n", "\033[1;31mWOLOLO\033[0m");
		if ((ft_get_timestamp() - aux->last_meal) / 1000 > args->t_die)
		{//revisar esto xq nunca entra aquí
			args->alive = false;
			ft_print("is dead", aux);
		}
		if (!pthread_mutex_unlock(&args->mutex_args))
			printf("\n%s\n\n", "\033[1;32mWOLOLO\033[0m");
		aux = philo->right;
		i++;
		usleep(100);
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
