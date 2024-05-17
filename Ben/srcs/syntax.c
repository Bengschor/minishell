/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschor <bschor@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 16:08:23 by bschor            #+#    #+#             */
/*   Updated: 2024/05/17 18:25:50 by bschor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"

int	last_pipe(t_system *systm)
{
	char	*tmp_prompt;

	tmp_prompt = readline("> ");
	if (!tmp_prompt)
		return (add_history(systm->prompt), ft_printf_err("\x1b[1A\x1b[2Cminishell: syntax error: unexpected end of file\n"));
	else if (tmp_prompt[0] != '\0')
		tmp_prompt = ft_strjoin_free(ft_strdup(" "), tmp_prompt);
	systm->prompt = ft_strjoin_free(systm->prompt, tmp_prompt);
	while (ft_isallspace(tmp_prompt))
	{
		tmp_prompt = readline("> ");
		if (!tmp_prompt)
			return (add_history(systm->prompt), ft_printf_err("\x1b[1A\x1b[2Cminishell: syntax error: unexpected end of file\n"));
		else if (tmp_prompt[0] != '\0')
			tmp_prompt = ft_strjoin_free(ft_strdup(" "), tmp_prompt);
		systm->prompt = ft_strjoin_free(systm->prompt, tmp_prompt);
	}
	return (0);
}

int	finish_by_pipe(char *str)
{
	int	i;

	i = ft_strlen(str);
	while (i > 0 && ft_isspace(str[i]))
		i--;
	if (str[i] == '|')
	{
		while (--i > 0 && ft_isspace(str[i]))
			;
		if (ft_strchr("<>", str[--i]))
		{
			if (str[--i] == '<')
				return (3);
			else
				return (2);
		}
		else
			return (1);
	}
	return (0);
}
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
int	quotes_by_pair(char *str, t_system *systm)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if ((str[i] == SQUOTE || str[i] == DQUOTE) && !str[i + 1])
			return (add_history(systm->prompt), ft_printf_err("not interpreting unclosed quotes\n"));
		if (str[i] == SQUOTE)
		{
			while (str[++i] && str[i] != SQUOTE)
				;
			if (!str[i] && str[i - 1] != SQUOTE)
				return (add_history(systm->prompt), ft_printf_err("not interpreting unclosed quotes\n"));
		}
		if (str[i] == DQUOTE)
		{
			while (str[++i] && str[i] != DQUOTE)
				;
			if (!str[i] && str[i - 1] != DQUOTE)
				return (add_history(systm->prompt), ft_printf_err("not interpreting unclosed quotes\n"));
		}
		i++;
	}
	return (EXIT_SUCCESS);
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
 * 12-15: Check if the last token is a special syntax token (HERED, APPEND,
 * INTO, OUTTO), and return an error message if it is.
 * 13: Return 0 if the syntax is valid.
 */
int	check_syntax(t_system *systm)
{
	t_lexer	*cur;

	cur = systm->lexer;
	if (cur->token == PIPE)
		return (ft_printf_err(TKNSTX, cur->token));
	while (cur->next)
	{
		if (finish_by_pipe(systm->prompt) == 2)
			return (ft_printf_err(TKNSSTX, "|"));
		if ((cur->token && cur->next->token) && ((ft_strchr("#=<>", cur->token)
			&& ft_strchr("#=<>|", cur->next->token))
			|| cur->token == cur->next->token))
			return (ft_printf_err(TKNSSTX, tkntostr(cur->next->token)));
		cur = cur->next;
	}
	if (cur->token == HERED || cur->token == APPEND || cur->token == INTO
		|| cur->token == OUTTO || finish_by_pipe(systm->prompt) == 3)
		return (ft_printf_err(NLSTX));
	return (0);
}
