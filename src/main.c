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

void	*routine(void)
{
	return 0;
}

void	ft_create_mutex(t_philo *lst_philo, t_args args)
{
	int		i;
	t_philo	*aux;

	i = 1;
	aux = lst_philo;
	while (i <= args.n_philo)
	{
		pthread_mutex_init(&aux->fork, NULL);
		if (aux->id % 2 != 0)
			pthread_mutex_lock(&aux->fork);
		else
			pthread_mutex_unlock(&aux->fork);
		aux = aux->right;
		i++;
	}
}

void	ft_destroy_mutex(t_philo *lst_philo, t_args args)
{
	int		i;
	t_philo	*aux;

	i = 1;
	aux = lst_philo;
	while (i <= args.n_philo)
	{
		pthread_mutex_destroy(&aux->fork);
		aux = aux->right;
		i++;
	}
}

int	main(int argc, char *argv[])
{
	t_args	args;
	t_philo	*lst_philo;
 atexit(leaks);
	if (!arg_number_manage(argc) || !atoi_args(argv, &args))
		return (1);
	lst_philo = 0;
	ft_create_philos(&lst_philo, args);
	// ft_lst_len(lst_philo);
	ft_link_list(lst_philo);
	//iniciar los mutex;
	ft_create_mutex(lst_philo, args);
	if (ft_create_threads(lst_philo, args, &routine))
		return (1);
	if (ft_join_threads(lst_philo, args))
		return (1);
	ft_destroy_mutex(lst_philo, args);
	ft_free_philos(lst_philo, args);
	return (0);
}
