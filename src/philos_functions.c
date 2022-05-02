#include "../inc/philo.h"

void	ft_create_philos(t_philo **lst_philo, t_args *args)
{
	int	i;

	i = 0;
	while (i < args->n_philo)
	{
		ft_lstadd_back(lst_philo, ft_lstnew(i + 1));
		i++;
	}
	return ;
}

void	ft_init_philos(t_philo	*lst_philo, t_args *args)
{
	int		i;

	i = 1;
	args->alive = true;
	args->hungry = true;
	while(i <= args->n_philo)
	{
		lst_philo->args = args;
		lst_philo->r_fork_id = i;
		if (lst_philo->id != 1)
			lst_philo->l_fork_id = i - 1;
		else
			lst_philo->l_fork_id = args->n_philo;
		lst_philo = lst_philo->right;
		lst_philo->meals = 0;
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
