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

void	ft_create_mutex(t_philo *lst_philo, t_args *args)
{
	int		i;
	t_philo	*aux;
//hay que gestionar la liberación y el cierre si la creación de los mutex fallan
	i = 1;
	aux = lst_philo;
	if (pthread_mutex_init(&args->mutex_life, NULL))
			printf("Problema creando el mutex de life nº\n");
	if (pthread_mutex_init(&args->mutex_print, NULL))
			printf("Problema creando el mutex de print nº\n");
	if (pthread_mutex_init(&args->mutex_satisfaction, NULL))
			printf("Problema creando el mutex de satisfaction nº\n");
	while (i <= args->n_philo)
	{
		if (pthread_mutex_init(&aux->fork, NULL))
			printf("Problema creando el mutex fork nº %d\n", aux->id);
		aux = aux->right;
		i++;
	}
}

void	ft_destroy_mutex(t_philo *lst_philo, t_args *args)
{
	int		i;
//hay que gestionar la liberación y el cierre si los destroy de los mutex fallan
	i = 1;
	if (pthread_mutex_destroy(&args->mutex_life))
			printf("Problema destruyendo el mutex de life\n");
	if (pthread_mutex_destroy(&args->mutex_print))
			printf("Problema destruyendo el mutex de print\n");
	if (pthread_mutex_destroy(&args->mutex_satisfaction))
			printf("Problema destruyendo el mutex de satisfaction\n");
	while (i <= args->n_philo)
	{
		if (pthread_mutex_destroy(&lst_philo->fork))
			printf("Problema destruyendo el mutex fork nº %d\n", lst_philo->id);
		lst_philo = lst_philo->right;
		i++;
	}
}
