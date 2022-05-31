/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads_functions.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josgarci <josgarci@student.42madrid.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/28 10:30:06 by josgarci          #+#    #+#             */
/*   Updated: 2022/05/28 10:30:07 by josgarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	ft_create_threads(t_philo *lst_philo, void *routine)
{
	int		i;

	i = 1;
	printf("%d\n", lst_philo->args->n_philo);
	while (i <= lst_philo->args->n_philo)
	{
		if (pthread_create(&lst_philo->thread, NULL, routine, lst_philo))
		{
			ft_free_philos(lst_philo, lst_philo->args);
			return (1);
		}
		lst_philo = lst_philo->right;
		i++;
	}
	return (0);
}

int	ft_join_threads(t_philo *lst_philo, t_args *args)
{
	int		i;
	t_philo	*aux;

	i = 1;
	aux = lst_philo;
	while (i <= args->n_philo)
	{
		if (pthread_join(aux->thread, NULL))
		{
			ft_free_philos(lst_philo, args);
			return (1);
		}
		aux = aux->right;
		i++;
	}
	return (0);
}

int	ft_create_mutex(t_philo *lst_philo, t_args *args)
{
	int		i;
	t_philo	*aux;

	i = 1;
	aux = lst_philo;
	if (pthread_mutex_init(&args->mutex_life, NULL))
		return (1);
	if (pthread_mutex_init(&args->mutex_print, NULL))
		return (2);
	if (pthread_mutex_init(&args->mutex_satisfaction, NULL))
		return (3);
	while (i <= args->n_philo)
	{
		if (pthread_mutex_init(&aux->fork, NULL))
			return (4);
		aux = aux->right;
		i++;
	}
	return (0);
}

int	ft_destroy_mutex(t_philo *lst_philo, t_args *args)
{
	int		i;

	i = 1;
	if (pthread_mutex_destroy(&args->mutex_life))
		return (1);
	if (pthread_mutex_destroy(&args->mutex_print))
		return (2);
	if (pthread_mutex_destroy(&args->mutex_satisfaction))
		return (3);
	while (i <= args->n_philo)
	{
		if (pthread_mutex_destroy(&lst_philo->fork))
			return (4);
		lst_philo = lst_philo->right;
		i++;
	}
	return (0);
}
