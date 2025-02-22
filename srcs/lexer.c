/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschor <bschor@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 09:55:46 by bschor            #+#    #+#             */
/*   Updated: 2024/07/24 18:55:54 by bschor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"

int	start_by_space(char *str)
{
	int	i;

	i = 0;
	while (str[i] && ft_isspace(str[i]))
		i++;
	return (i);
}

static int	add_lexer(t_system *systm, char *str, int token)
{
	t_lexer	*new;
	t_lexer	*current;

	new = malloc(sizeof(t_lexer));
	if (!new)
		return (free(str), free_all(systm, CRASH), 1);
	new->str = str;
	new->token = token;
	new->next = NULL;
	if (systm->lexer == NULL)
	{
		systm->lexer = new;
		new->prev = NULL;
		return (0);
	}
	current = systm->lexer;
	while (current->next)
		current = current->next;
	current->next = new;
	new->prev = current;
	return (0);
}

static int	join_words(t_system *systm)
{
	t_lexer	*current;

	current = systm->lexer;
	while (current && current->next)
	{
		if ((current->token == DQUOTE || current->token == SQUOTE
				|| (!current->token
					&& !ft_strchr(current->str
						+ start_by_space(current->str), ' ')
					&& !ft_isallspace(current->str)))
			&& (current->next->token == DQUOTE
				|| current->next->token == SQUOTE
				|| (!current->next->token
					&& !ft_strchr(current->next->str, ' '))))
		{
			if (!ft_nodjoin(current, current->next))
				return (free_all(systm, CRASH), 1);
		}
		else
			current = current->next;
	}
	return (0);
}

static int	ft_lextrim(t_system *systm)
{
	t_lexer	*current;
	char	*tmp;

	current = systm->lexer;
	if (current && !current->token && ft_isallspace(current->str))
		systm->lexer = systm->lexer->next;
	while (current)
	{
		if (current->str && !current->token)
		{
			tmp = ft_strtrim(current->str, "\t\n ");
			if (!tmp)
				return (free_all(systm, CRASH), 1);
			free(current->str);
			current->str = tmp;
		}
		if (!current->token && ft_isallspace(current->str))
			del_node(&current);
		else
			current = current->next;
	}
	return (0);
}

void	ft_lexer(t_system	*systm)
{
	int	i;

	i = 0;
	while (systm->prompt[i])
	{
		if (systm->prompt[i] == SQUOTE)
			add_lexer(systm, handle_quote(systm, &i), SQUOTE);
		else if (systm->prompt[i] == DQUOTE)
			add_lexer(systm, handle_quote(systm, &i), DQUOTE);
		else if ((systm->prompt[i] == PIPE) || (systm->prompt[i] == INTO)
			|| (systm->prompt[i] == OUTTO))
			add_lexer(systm, NULL, handle_token(systm, &i));
		else
			add_lexer(systm, handle_word(systm, &i), 0);
		i++;
	}
	expander(systm);
	join_words(systm);
	ft_lextrim(systm);
}
