/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschor <bschor@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 16:08:23 by bschor            #+#    #+#             */
/*   Updated: 2024/05/10 13:12:25 by bschor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"
/**
 * @brief Checks if quotes in the string occur in pairs.
 * 
 * @param str The string to check.
 * @return EXIT_SUCCESS if quotes occur in pairs, EXIT_FAILURE otherwise.
 * @line by line:
 * 1-2: Initialize the index variable.
 * 3-18: Iterate through the string, checking if single and double quotes
 * occur in pairs.
 * 4-9: Check for single quotes and verify if each opening quote has a
 * corresponding closing quote.
 * 11-16: Check for double quotes and verify if each opening quote has a
 * corresponding closing quote.
 * 19: Return EXIT_SUCCESS if all quotes occur in pairs, EXIT_FAILURE
 * otherwise.
 */
int	quotes_by_pair(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if ((str[i] == SQUOTE || str[i] == DQUOTE) && !str[i + 1])
			return (printf("not interpreting unclosed quotes\n"));
		if (str[i] == SQUOTE)
		{
			while (str[++i] && str[i] != SQUOTE)
				;
			if (!str[i] && str[i - 1] != SQUOTE)
				return (printf("not interpreting unclosed quotes\n"));
		}
		if (str[i] == DQUOTE)
		{
			while (str[++i] && str[i] != DQUOTE)
				;
			if (!str[i] && str[i - 1] != DQUOTE)
				return (printf("not interpreting unclosed quotes\n"));
		}
		i++;
	}
	return (EXIT_SUCCESS);
}

/**
 * @brief Checks if the last token in the lexer linked list is a valid
 * syntax.
 * 
 * @param last A pointer to the last node in the lexer linked list.
 * @return 0 if the syntax is valid, a non-zero value otherwise.
 * @line by line:
 * 1-6: Check if the last token is a special syntax token (HERED, APPEND,
 * INTO, OUTTO),
 *      and return an error message if it is.
 * 7: Return 0 if the syntax is valid.
 */
static int	check_syntax_last(t_lexer *last)
{
	if (last->token == HERED || last->token == APPEND || last->token == INTO
		|| last->token == OUTTO)
		return (printf(NLSTX));
	return (0);
}

/**
 * @brief Checks the syntax of the lexer linked list.
 * 
 * @param systm A pointer to the system struct.
 * @return 0 if the syntax is valid, a non-zero value otherwise.
 * @line by line:
 * 1-6: Iterate through the lexer linked list and check for consecutive 
 	identical tokens.
 * 7-9: Check if the last token is a valid syntax token.
 * 10-12: Return an error message if the syntax is invalid.
 * 13: Return 0 if the syntax is valid.
 */
int	check_syntax(t_system *systm)
{
	t_lexer	*current;

	current = systm->lexer;
	if (current->token == PIPE)
		return (printf(TKNSTX, current->token));
	while (current->next)
	{
		if (ft_strchr("<>|", current->token) && current->token
			&& current->token == current->next->token)
			return (printf(TKNSTX, current->token));
		if (ft_strchr("#=", current->token) && current->token
			&& current->token == current->next->token)
			return (printf(TKNSSTX, tkntostr(current->token)));
		current = current->next;
	}
	if (check_syntax_last(current))
		return (1);
	return (0);
}
