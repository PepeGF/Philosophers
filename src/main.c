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
		ft_lstadd_back(lst_philo, ft_lstnew(i + 1));
		i++;
	}
	return ;
}

void	ft_link_list(t_philo *lst_philo)
{
	t_philo *aux;

	aux = lst_philo;
	while (aux)
	{
		if (aux->right)
			aux->right->left = aux;
		else
		{
			lst_philo->left = aux;
			aux->right = lst_philo;
			break;
		}
		aux = aux->right;
	}
	aux = lst_philo;
/*	int i = 1;
	while (i <= 20)
	{
		printf("Filo nº: %d, filo de la dcha: %d\n", aux->id, aux->right->id);
		i++;
		aux = aux->right;
	}*/
}

void	ft_free_philos(t_philo *lst_philo, t_args args)
{
	t_philo	*aux;
	t_philo	*aux2;
	int		i;

	i = 1;
	aux = lst_philo;
	while (i < args.n_philo)
	{
		aux2 = aux;
		aux = aux->right;
		free(aux2);
		i++;
	}
	free(aux);
	return ;
}

void	ft_init_philos(t_philo	*lst_philo, t_args args)
{
	t_philo	*aux;
	int		i;
(void)aux;
(void)lst_philo;
	i = 1;
	while(i <= args.n_philo)
	{
		i++;
	}
}

void	*routine(void)
{
	printf("%s\n", "Soy un HILO");
	usleep(1000);
	printf("%s\n", "Viva er Betis");
	return 0;
}

int	ft_create_threads(t_philo *lst_philo, t_args args, void *routine)
{
	int	i;

	i = 1;
	while (i <= args.n_philo)
	{
		if (pthread_create(&lst_philo->thread, NULL, routine, NULL))
		{
			ft_free_philos(lst_philo, args);
			return (1);
		}
		i++;
	}
	return (0);
}

int	ft_join_threads(t_philo *lst_philo, t_args args)
{
	int	i;

	i = 0;
	while (i <= args.n_philo)
	{
		if (pthread_join(lst_philo->thread, NULL))
		{
			ft_free_philos(lst_philo, args);
			return (1);
		}
		i++;
	}
	return (0);
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
	if (ft_create_threads(lst_philo, args, &routine))
		return (1);
	if (ft_join_threads(lst_philo, args))
		return (1);
	printf("%s\n", "Aunque el Atleti mola más");
	ft_free_philos(lst_philo, args);
	return (0);
}
