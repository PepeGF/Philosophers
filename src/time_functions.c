/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josgarci <josgarci@student.42madrid.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/28 10:30:18 by josgarci          #+#    #+#             */
/*   Updated: 2022/05/28 10:30:20 by josgarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	ft_get_timestamp(void)
{
	int				wololo;
	struct timeval	time;

	gettimeofday(&time, NULL);
	wololo = time.tv_sec * 1000 + time.tv_usec / 1000;
	return (wololo);
}

void	ft_set_zero_time(t_args *args)
{
	args->zero_time = ft_get_timestamp();
	return ;
}
