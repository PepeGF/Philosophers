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

void	ft_create_philos(t_philo **lst_philo, t_args args)
{
	int	i;

	i = 0;
	while (i < args.n_philo)
	{
		ft_lstadd_back(lst_philo, ft_lstnew(i));
		i++;
	}
	return ;
}

void	ft_free_philos(t_philo *lst_philo)
{
	t_philo	*aux;
	t_philo	*aux2;

	aux = lst_philo;
	while (aux)
	{
		aux2 = aux;
		aux = aux->right;
		free(aux2);
	}
	free(aux);
	return ;
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
	ft_free_philos(lst_philo);
	return (0);
}
