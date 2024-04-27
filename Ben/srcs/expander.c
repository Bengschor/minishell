/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschor <bschor@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 10:51:52 by bschor            #+#    #+#             */
/*   Updated: 2024/04/27 15:31:09 by bschor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"

/**
 * @brief Expands an environment variable in the given string.
 * 
 * @param str A pointer to the original string.
 * @param i The index where the dollar sign ('$') is located in the string.
 * @param systm A pointer to the system struct.
 * @return The length of the replaced substring if successful, otherwise a 
 * negative value indicating an error.
 * @line by line:
 * 1-7: Extract the substring to be expanded from the original string,
 * starting from the index after the dollar sign.
 * 8: Search for the corresponding environment variable using the extracted 
 * substring.
 * 9: If a matching environment variable is found:
 * 10: Extract the value part of the environment variable.
 * 11: Replace the substring in the original string with the value of
 * the environment variable.
 * 12-14: Free the memory allocated for the extracted substring.
 * 15: Return the length of the replaced substring if successful, or
 * a negative value indicating an error.
 */
int	exp_env_var(char **str, int i, t_system *systm)
{
	char	*to_exp;
	char	*env_var;
	int		env_var_len;

	to_exp = ft_substr(*str, i + 1, find_next_alnum((*str) + i + 1));
	if (!to_exp)
		return (ft_crash(systm), 1);
	env_var = ft_strchr(is_env_var(to_exp, systm->env), '=');
	if (env_var)
		env_var++;
	if (ft_strrpl(str, i, ft_strlen(to_exp) + 1, env_var))
		return (ft_crash(systm), -10000000);
	env_var_len = ft_strlen(env_var);
	free(to_exp);
	return (env_var_len);
}

/**
 * @brief Replaces the "$?" substring in the original string with the exit
 * status of the previous command.
 * 
 * @param i The index where the "$?" substring is located in the string.
 * @param str A pointer to the original string.
 * @param systm A pointer to the system struct.
 * @return The length of the replaced substring if successful, otherwise a
 * negative value indicating an error.
 * @line by line:
 * 1-3: Convert the exit status to a string.
 * 4-7: Replace the "$?" substring in the original string with the exit status
 * string.
 * 8: Free the memory allocated for the exit status string.
 * 9: Return the length of the replaced substring if successful, or a negative
 * value indicating an error.
 */
static int	exp_exit_status(int i, char **str, t_system *systm)
{
	char	*nbr_string;
	int		len_nbr;

	nbr_string = ft_itoa(systm->status);
	if (!nbr_string)
		return (ft_crash(systm), -10000000);
	if (ft_strrpl(str, i, 2, nbr_string))
		return (ft_crash(systm), -10000000);
	len_nbr = ft_strlen(nbr_string);
	free(nbr_string);
	return (len_nbr);
}

/**
 * @brief Expands environment variables and exit status in the given string.
 * 
 * @param str A pointer to the string to be expanded.
 * @param systm A pointer to the system struct.
 * @line by line:
 * 1-9: Iterate through the string character by character.
 * 2-8: Check if the current character indicates an environment variable,
 * exit status, or neither, and expand accordingly.
 * 10-12: Update the index based on the length of the replaced substring or
 * the expanded environment variable.
 */
void	expand_str(char **str, t_system *systm)
{
	int	i;

	i = 0;
	while (i >= 0 && (*str)[i])
	{
		if ((*str)[i] == '$' && (*str)[i + 1] == '?')
			i = i + exp_exit_status(i, str, systm);
		else if (i >= 0 && (*str)[i] == '$'
			&& (!ft_isalnum((*str)[i + 1]) || (*str)[i + 1] == '_'))
			i++;
		else if (i >= 0 && (*str)[i] == '$')
			i += exp_env_var(str, i, systm);
		else
			i++;
	}
}

/*
sends a node to get expended only if it is a DQUOTED string or not quoted

a verifier avec strings
*/
void	expander(t_system *systm)
{
	t_lexer	*current;

	current = systm->lexer;
	while (current)
	{
		if (current->str && (current->token == DQUOTE || !current->token))
			expand_str(&(current->str), systm);
		current = current->next;
	}
}
