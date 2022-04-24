#include "../inc/philo.h"

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

void	ft_init_philos(t_philo	*lst_philo, t_args args)
{
	t_philo	*aux;
	int		i;
(void)aux;
(void)lst_philo;
	aux = lst_philo;
	i = 1;
	while(i <= args.n_philo)
	{
		aux = aux->right;
		i++;
	}
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
