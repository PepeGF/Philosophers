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

void	*routine(void *philo)
{
	int	start;
	int	end;
	int	elapsed;
	struct timeval	moment;

	gettimeofday(&moment, NULL);
	start = moment.tv_sec * 1000000 + moment.tv_usec;
	usleep(1 / ((t_philo *)philo)->id);
	printf("Hola, soy el filósofo nº %d\n", ((t_philo *)philo)->id);
	gettimeofday(&moment, NULL);
	end = moment.tv_sec * 1000000 + moment.tv_usec;
	elapsed = end - start;
	printf("Soy el \033[7;32m%d\033[0m, he tardado\033[31m %d\033[0m\n", ((t_philo *)philo)->id, elapsed);
	/*// printf("%d\n", start);
	usleep(1500000);
	gettimeofday(&moment, NULL);
	end = moment.tv_sec * 1000000 + moment.tv_usec;
	// printf("%d\n", end);
	elapsed = end - start;
	printf("%d\n", elapsed);*/
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
/*		if (aux->id % 2 != 0)
			pthread_mutex_lock(&aux->fork);
		else
			pthread_mutex_unlock(&aux->fork);*/
		aux = aux->right;
		i++;
	}
	i = 1;
	aux = lst_philo;
	while (i <= args.n_philo)
	{

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

/*t_data	*ft_init_data(t_philo *lst_philo, t_args *args)
{
	t_data *data;

	data = malloc (sizeof(t_data *));
	data->args = args;
	data->lst_philo = lst_philo;
	return (data);
}*/

int	main(int argc, char *argv[])
{
	t_args	args;
	t_philo	*lst_philo;
	// t_data	*data;
// atexit(leaks);
	if (!arg_number_manage(argc) || !atoi_args(argv, &args))
		return (1);
	lst_philo = 0;
	ft_create_philos(&lst_philo, args);
	// ft_lst_len(lst_philo);
	ft_link_list(lst_philo);
	ft_init_philos(lst_philo, args);

	//iniciar los mutex;
	ft_create_mutex(lst_philo, args);
	// data = ft_init_data(lst_philo, &args);
	if (ft_create_threads(lst_philo, &routine))
		return (1);
	if (ft_join_threads(lst_philo, args))
		return (1);
	ft_destroy_mutex(lst_philo, args);
	ft_free_philos(lst_philo, args);
	return (0);
}
