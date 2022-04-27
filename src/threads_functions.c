#include "../inc/philo.h"

int	ft_create_threads(t_data *data, void *routine)
{
	int		i;
	t_philo	*aux;

	i = 1;
	aux = data->lst_philo;
	while (i <= data->args->n_philo)
	{
		if (pthread_create(&aux->thread, NULL, routine, data))
		{
			ft_free_philos(data->lst_philo, *data->args);
			return (1);
		}
		aux = aux->right;
		i++;
	}
	return (0);
}

int	ft_join_threads(t_philo *lst_philo, t_args args)
{
	int		i;
	t_philo	*aux;

	i = 1;
	aux = lst_philo;
	while (i <= args.n_philo)
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
