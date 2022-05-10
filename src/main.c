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

void	*routine(void *philo)
{
	t_philo *ph;
	t_args	*args;
	
	ph = (t_philo *)philo;
	args = ph->args;
	if (ph->id % 2 == 0)
		usleep(1000); //si no funciona dejar un valor fijo
	while (args->alive == true)
	{
		ft_eating(ph);
		ft_sleeping(ph);
		if (args->n_meal != 0 && ph->meals == args->n_meal)
			break;
		ft_thinking(ph);
	}

	return (NULL);
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
//	ft_check_status(lst_philo, args);
	if (ft_join_threads(lst_philo, args))
		return (1);
	ft_destroy_mutex(lst_philo, args);
	ft_free_philos(lst_philo, args);
	//free(args); //ojo con estoooooooooooooooooo, hay que liberarlo en más sitios
	return (0);
}
