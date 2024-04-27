/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschor <bschor@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 15:48:24 by bschor            #+#    #+#             */
/*   Updated: 2024/04/27 15:32:53 by bschor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"

/**
 * @brief Frees memory allocated for an array of strings.
 * 
 * @param strs The array of strings to be freed.
 * @line by line:
 * 1-5: Initialize the index variable i to 0.
 * 6-9: Iterate over the array of strings and free each string.
 * 10: Free the memory allocated for the array of string pointers.
 */
void	free_strs(char **strs)
{
	int	i;

	i = 0;
	while (strs && strs[i])
	{
		free(strs[i]);
		i++;
	}
	free(strs);
}

/**
 * @brief Frees memory allocated for an array of strings and crashes.
 * 
 * @param strs The array of strings to be freed.
 * @param i The index used for freeing strings in reverse order.
 * @line by line:
 * 1-4: Iterate over the array of strings in reverse order and free each
 * string.
 * 5: Free the memory allocated for the array of string pointers.
 */
void	free_strs_crash(char **strs, int i)
{
	while (i > 0)
	{
		free(strs[i]);
		i--;
	}
	free(strs);
}

/**
 * @brief Adds a string to an array of strings.
 * 
 * @param array The array of strings to which the string will be added.
 * @param str The string to be added.
 * @return The updated array of strings with the added string.
 * @line by line:
 * 1-6: Initialize variables and allocate memory for the new array.
 * 7-14: Copy existing strings from the original array to the new array.
 * 15-19: Add the new string to the new array and handle memory allocation
 * errors.
 * 20-21: Return the updated array of strings.
 */
char	**ft_addstr(char **array, char *str)
{
	int		len;
	int		i;
	char	**new;

	i = 0;
	len = ft_strslen(array);
	new = malloc(sizeof(char *) * (len + 2));
	if (!new)
		return (NULL);
	while (i < len)
	{
		new[i] = ft_strdup(array[i]);
		if (!new[i])
			return (free_strs_crash(new, i), NULL);
		i++;
	}
	new[i] = ft_strdup(str);
	if (!new[i])
		return (free_strs_crash(new, i), NULL);
	new[i + 1] = NULL;
	return (new);
}

/**
 * @brief Adds the current word to the parser array.
 * 
 * @param systm A pointer to the system struct.
 * @param exec_i The index of the current command.
 * @return 0 on success, 1 on failure.
 * @line by line:
 * 1-5: Add the current word to the parser array.
 * 6-9: Handle memory allocation errors and update the parser array.
 * 10-11: Return 0 on success.
 */
int	add_word(t_system *systm, int exec_i)
{
	char	**tmp;

	printf("add_word exec_i:%d\n", exec_i);
	tmp = ft_addstr(systm->parser[exec_i].strs, systm->lexer->str);
	if (!tmp)
		return (ft_crash(systm), 1);
	free_strs(systm->parser[exec_i].strs);
	systm->parser[exec_i].strs = tmp;
	return (0);
}

/**
 * @brief Counts the number of pipe tokens in the lexer linked list.
 * 
 * @param lexer A pointer to the lexer linked list.
 * @return The number of pipe tokens.
 * @line by line:
 * 1: Initialize the variable pipes to 0.
 * 2: Check if the lexer linked list exists.
 * 3: Increment the number of pipes if the current token is a pipe.
 * 4-5: Move to the next node in the lexer linked list.
 * 6: Return the total number of pipe tokens.
 */
int	count_pipes(t_lexer *lexer)
{
	int	pipes;

	pipes = 0;
	if (lexer)
		pipes++;
	while (lexer)
	{
		if (lexer->token == PIPE)
			pipes++;
		lexer = lexer->next;
	}
	return (pipes);
}
