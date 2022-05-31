/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josgarci <josgarci@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 20:23:09 by josgarci          #+#    #+#             */
/*   Updated: 2022/05/31 20:23:13 by josgarci         ###   ########.fr       */
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
