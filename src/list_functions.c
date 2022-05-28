/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josgarci <josgarci@student.42madrid.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/28 10:29:25 by josgarci          #+#    #+#             */
/*   Updated: 2022/05/28 10:29:27 by josgarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
}
