/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arguments_manage.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josgarci <josgarci@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/22 17:20:13 by josgarci          #+#    #+#             */
/*   Updated: 2022/04/22 18:25:13 by josgarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../inc/philo.h"

int	arg_number_manage(int argc)
{
	if (argc < 5)
	{
		write(1, "Too few arguments, at least 4 needed\n", 37);
	}
	if (argc > 6)
	{
		write(1, "Too many arguments, at most 5 needed\n", 37);
	}
	if (argc < 5 || argc > 6)
	{
		write(1, "Usage: philo number_of_philosophers time_to_die ", 48);
		write(1, " time_to_eat time_to_sleep [number_of_times_each", 48);
		write(1, "_philosopher_must_eat]\n", 23);
		return (0);
	}
	return (1);
}

int	atoi_args(char **argv, t_args *args)
{
	int	i;
	int	matrix[5];

	i = 1;
	while (argv[i])
	{
		matrix[i - 1] = ft_atoi(argv[i]);
		if (matrix [i - 1] <= 0)
		{
			write(1, "Wrong argument\n", 15);
			return (0);
		}
		i++;
	}
	i = 0;
	args->n_philo = matrix[i++];
	args->t_die = matrix[i++];
	args->t_eat = matrix[i++];
	args->t_sleep = matrix[i++];
	if (argv[i + 1])
		args->n_meal = matrix[i];
	return (1);
}
