/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschor <bschor@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 14:14:27 by bschor            #+#    #+#             */
/*   Updated: 2024/07/24 18:55:44 by bschor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"

void	del_node(t_lexer **node)
{
	t_lexer	*tmp;

	tmp = (*node)->next;
	free((*node)->str);
	if ((*node)->prev)
		(*node)->prev->next = (*node)->next;
	if ((*node)->next)
		(*node)->next->prev = (*node)->prev;
	free(*node);
	*node = tmp;
}

int	ft_nodjoin(t_lexer *first, t_lexer *second)
{
	char	*tmp;

	tmp = ft_strjoin(first->str + start_by_space(first->str), second->str);
	if (!tmp)
		return (0);
	free(first->str);
	free(second->str);
	first->str = tmp;
	if (second->prev)
		second->prev->next = second->next;
	if (second->next)
		second->next->prev = second->prev;
	if (second->token && !first->token)
		first->token = second->token;
	free(second);
	return (1);
}

char	*handle_quote(t_system *systm, int *i)
{
	char	quote;
	int		len;
	char	*word;

	quote = systm->prompt[*i];
	(*i)++;
	len = 0;
	while (systm->prompt[(*i) + len] && systm->prompt[(*i) + len] != quote)
		len++;
	word = ft_substr(systm->prompt, *i, len);
	if (!word)
		return (free_all(systm, CRASH), NULL);
	(*i) += len;
	return (word);
}

char	*handle_word(t_system *systm, int *i)
{
	char	*word;
	int		len;
	char	*prompt;

	len = 0;
	prompt = systm->prompt;
	while (prompt[(*i) + len] && ft_isspace(prompt[(*i) + len]))
		len++;
	while (prompt[(*i) + len] && !ft_strchr("\'\"|<> ", prompt[(*i) + len]))
		len++;
	word = ft_substr(systm->prompt, *i, len);
	if (!word)
		return (free_all(systm, CRASH), NULL);
	(*i) += len - 1;
	return (word);
}

int	handle_token(t_system *systm, int *i)
{
	int		token;
	char	*prompt;

	prompt = systm->prompt;
	token = prompt[*i];
	if (token == INTO && prompt[(*i) + 1] == INTO)
		token = HERED;
	if (token == OUTTO && prompt[(*i) + 1] == OUTTO)
		token = APPEND;
	if (token == HERED || token == APPEND)
		*i += 1;
	return (token);
}
