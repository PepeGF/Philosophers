/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos_functions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josgarci <josgarci@student.42madrid.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/28 10:29:41 by josgarci          #+#    #+#             */
/*   Updated: 2022/05/28 10:29:42 by josgarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

static void	ft_free_list(t_philo **lst_philo)
{
	t_philo	*aux;
	t_philo	*aux2;

	aux = *lst_philo;
	while (aux)
	{
		aux2 = aux;
		aux = aux->right;
		free(aux2);
	}
}

int	ft_create_philos(t_philo **lst_philo, t_args *args)
{
	int		i;
	t_philo	*aux;

	i = 0;
	while (i < args->n_philo)
	{
		aux = ft_lstnew(i + 1);
		if (!aux)
		{
			//revisar esto con valgrind
			free((*lst_philo)->args);
			ft_free_list(lst_philo);
			return (1);
		}
		else
			ft_lstadd_back(lst_philo, aux);
		i++;
	}
	return (0);
}

void	ft_init_philos(t_philo	*lst_philo, t_args *args)
{
	int		i;

	i = 1;
	args->alive = true;
	args->hungry = true;
	while (i <= args->n_philo)
	{
		lst_philo->args = args;
		lst_philo->hungry = true;
		lst_philo->meals = 0;
		lst_philo->last_meal = 0;
		lst_philo = lst_philo->right;
		i++;
	}
}

void	ft_free_philos(t_philo *lst_philo, t_args *args)
{
	t_philo	*aux;
	t_philo	*aux2;
	int		i;

	i = 1;
	aux = lst_philo;
	while (i < args->n_philo)
	{
		aux2 = aux;
		aux = aux->right;
		free(aux2);
		i++;
	}
	free(aux);
	free(args);
	return ;
}
