/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschor <bschor@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 14:14:27 by bschor            #+#    #+#             */
/*   Updated: 2024/04/27 15:37:51 by bschor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"

/**
 * @brief Deletes a node from the lexer.
 * 
 * @param node A pointer to the node to be deleted.
 * @line by line:
 * 1: Saves the next node.
 * 2-3: Frees the string associated with the node.
 * 4-7: Adjusts the pointers of the neighboring nodes.
 * 8: Frees the node itself and updates the pointer.
 */
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

/**
 * @brief Joins the string content of two lexer nodes.
 * 
 * @param first The first lexer node.
 * @param second The second lexer node.
 * @return 1 if successful, 0 otherwise.
 * @line by line:
 * 1-3: Joins the strings of the first and second nodes.
 * 4-6: Frees the string contents of the nodes.
 * 7-10: Adjusts the pointers of the neighboring nodes.
 * 11: Frees the second node.
 */
int	ft_nodjoin(t_lexer *first, t_lexer *second)
{
	char	*tmp;

	tmp = ft_strjoin(first->str, second->str);
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

/**
 * @brief waits for the second quote and duplicates the smaller string
 * 
 * @param systm A pointer to the system struct.
 * @param i A pointer to the current index in the prompt string.
 * @return The parsed quoted string.
 * @line by line:
 * 1: Retrieves the quote character.
 * 2: Increments the index to skip the quote character.
 * 3-4: Calculates the length of the quoted string.
 * 5-7: Extracts the quoted string.
 *  8: increments i by the length of the quoted string
 */
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
		return (ft_crash(systm), NULL);
	(*i) += len;
	return (word);
}

/**
 * @brief waits until and of prompt or token and duplicates the smaller string
 * 
 * @param systm A pointer to the system struct.
 * @param i A pointer to the current index in the prompt string.
 * @return The parsed word.
 * @line by line:
 * 1-2: Initializes variables.
 * 3-5: Skips leading whitespace.
 * 6-8: Finds the end of the word.
 * 9: increments i by the length - 1 (pq deja ??)
 */
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
		return (ft_crash(systm), NULL);
	(*i) += len - 1;
	return (word);
}

/**
 * @brief returns the right token and increments the value of i by the right
 * amount
 * 
 * @param systm A pointer to the system struct.
 * @param i A pointer to the current index in the prompt string.
 * @return The token character.
 * @line by line:
 * Retrieves the token character from the prompt.
 * Adjusts index and token for double characters (e.g., "<<").
 */
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
