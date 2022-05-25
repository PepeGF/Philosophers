#include "../inc/philo.h"

t_philo	*ft_lstlast(t_philo *lst)
{
	if (!lst)
		return (0);
	while (lst->right)
		lst = lst->right;
	return (lst);
}

void	ft_lstadd_back(t_philo **lst, t_philo *new)
{
	t_philo	*old_last;

	if (!*lst)
	{
		*lst = new;
		return ;
	}
	if (!new)
		return ;
	old_last = ft_lstlast(*lst);
	old_last->right = new;
}

t_philo	*ft_lstnew(int id)
{
	t_philo	*new;

	new = (t_philo *)malloc(sizeof(t_philo));
	if (!new)
		return (NULL);
	new->id = id;
	new->right = NULL;
	return (new);
}

void	ft_link_list(t_philo *lst_philo)
{
	t_philo	*aux;

	aux = lst_philo;
	while (aux)
	{
		if (aux->right)
			aux->right->left = aux;
		else
		{
			lst_philo->left = aux;
			aux->right = lst_philo;
			break ;
		}
		aux = aux->right;
	}
/*	aux = lst_philo;
	int i = 1;
	while (i <= args->n_philo)
	{
		printf("Filo nº: %d, filo de la dcha: %d\n", aux->id, aux->right->id);
		i++;
		aux = aux->right;
	}*/
}
