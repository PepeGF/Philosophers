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

int	ft_check_satisfaction(t_philo *philo, t_args *args)
{
	int		i;
	int		satisfied;
	t_philo	*aux;

	i = 0;
	satisfied = 0;
	aux = philo;
	while (i < args->n_philo)
	{
		if (aux->hungry == false)
			satisfied++;
		aux = aux->right;
		i++;
	}
	return (satisfied);
}

void	ft_check_status(t_philo *philo, t_args *args)
{
	t_philo	*aux;

	aux = philo;
	if (args->n_philo == 1)
		usleep(args->t_die * 500);
	while (1)
	{
		pthread_mutex_lock(&args->mutex_life);
		if (args->alive == false || args->satisfied == args->n_philo)
		{
			pthread_mutex_unlock(&args->mutex_life);
			break ;
		}
		if (ft_get_timestamp() - aux->last_meal >= args->t_die)
		{
			ft_print("is dead", aux);
			args->alive = false;
		}
		pthread_mutex_unlock(&args->mutex_life);
		aux = aux->right;
		usleep(300);
		if (aux == philo->left && args->n_philo != 1)
			usleep(1000);
	}
}

int	ft_first_part(int argc, char *argv[], t_philo **lst_philo, t_args *args)
{
	if (arg_number_manage(argc, args))
		return (2);
	if (atoi_args(argv, args))
		return (2);
	if (ft_create_philos(lst_philo, args))
		return (3);
	ft_link_list(*lst_philo);
	ft_init_philos(*lst_philo, args);
	if (ft_create_mutex(*lst_philo, args))
	{
		ft_free_philos(*lst_philo, args);
		return (4);
	}
	return (0);
}

int	ft_second_part(t_philo *lst_philo, t_args *args)
{
	(void)lst_philo;
	(void)args;
	if (ft_create_threads(lst_philo, &routine))
	{
		ft_free_philos(lst_philo, args);
		return (5);
	}
	usleep(800);
	ft_check_status(lst_philo, args);
	if (ft_join_threads(lst_philo, args))
	{
		ft_free_philos(lst_philo, args);
		return (6);
	}
	if (ft_destroy_mutex(lst_philo, args))
	{
		ft_free_philos(lst_philo, args);
		return (7);
	}
	return (0);
}

int	main(int argc, char *argv[])
{
	t_args		*args;
	t_philo		*lst_philo;

	lst_philo = 0;
	args = malloc(sizeof(t_args));
	if (!args)
		return (1);
	if (ft_first_part(argc, argv, &lst_philo, args))
		return (2);
	args->zero_time = ft_get_timestamp();
	if (ft_second_part(lst_philo, args))
		return (3);
	ft_free_philos(lst_philo, args);
	return (0);
}
