/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   crash.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschor <bschor@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 11:47:11 by bschor            #+#    #+#             */
/*   Updated: 2024/04/26 15:50:23 by bschor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"

t_lexer	*find_first(t_lexer *node)
{
	while (node->prev)
		node = node->prev;
	return (node);
}

void	free_lexer(t_lexer *first)
{
	t_lexer	*current;
	t_lexer	*tmp;

	current = first;
	while (current)
	{
		tmp = current->next;
		free(current->str);
		free(current);
		current = tmp;
	}
}

void	ft_crash(t_system *systm)
{
	int	j;

	j = -1;
	if (systm->lexer)
		free_lexer(find_first(systm->lexer));
	if (systm->parser)
	{
		while (systm->parser[++j].strs)
			free_strs(systm->parser[j].strs);
		free(systm->parser);
	}
}
