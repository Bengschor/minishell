/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschor <bschor@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 23:07:57 by bschor            #+#    #+#             */
/*   Updated: 2023/10/20 13:33:54 by bschor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_before_last(t_list *lst)
{
	t_list	*current;

	if (!lst)
		return (NULL);
	current = lst;
	while (current->next && (current->next)->next)
		current = current->next;
	return (current);
}

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*last;
	t_list	*first;

	if (!lst || !del || !*lst)
		return ;
	first = *lst;
	last = ft_before_last(first);
	while (last->next)
	{
		free((last->next)->next);
		ft_lstdelone(last->next, del);
		last->next = NULL;
		last = ft_before_last(first);
	}
	if (last && last->next)
		free(last->next);
	ft_lstdelone(last, del);
	*lst = NULL;
}
