/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschor <bschor@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 15:01:18 by bschor            #+#    #+#             */
/*   Updated: 2024/04/27 15:34:59 by bschor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"

/**
 * @brief Replaces a substring in a string with another substring.
 * 
 * @param origin A pointer to the original string.
 * @param start The starting index of the substring to be replaced.
 * @param len_del The length of the substring to be replaced.
 * @param rpl The replacement substring.
 * @return 0 on success, 1 on failure.
 * @line by line:
 * Compute the length of the replacement substring.
 * Calculate the length of the new string after replacement.
 * Allocate memory for the new string.
 * Copy the part of the original string that occurs before the replacement.
 * Concatenate the replacement substring.
 * Concatenate the part of the original string that comes after the replaced
 * substring.
 * Free the original string and update it with the new one.
 */
int	ft_strrpl(char **origin, int start, int len_del, char *rpl)
{
	char	*new;
	int		len_new;
	int		len_rpl;

	len_rpl = ft_strlen(rpl);
	len_new = ft_strlen(*origin) + len_rpl - len_del;
	new = malloc(sizeof(char) * (len_new + 1));
	if (!new)
		return (1);
	new[len_new] = 0;
	ft_strlcpy(new, *origin, start + 1);
	ft_strlcat(new + start, rpl, len_new + 1);
	ft_strlcat(new + start + len_rpl, *origin + start + len_del,
		len_new - start - len_rpl + 1);
	free(*origin);
	*origin = new;
	return (0);
}

/**
 * @brief Finds the index of the next non-alphanumeric character or underscore
 * in the string.
 * @param str The input string to be searched.
 * @return The index of the next non-alphanumeric character or underscore.
 * @line by line:
 * 1-2: Initialize the index variable i to 0.
 * 3-5: Iterate through the string until a non-alphanumeric character or
 * underscore is encountered.
 * 6: Return the index i when the first non-alphanumeric character or
 * underscore is found.
*/
int	find_next_alnum(char *str)
{
	int	i;

	i = 0;
	while (str[i] && (ft_isalnum(str[i]) || str[i] == '_'))
		i++;
	return (i);
}

/**
 * @brief Searches for an environment variable that matches the given string.
 * 
 * @param str The string to search for in the environment variables array.
 * @param env The array of environment variables.
 * @return The matching environment variable if found, otherwise NULL.
 * @line by line:
 * 4: Check if the length of the string matches the length of the current
 * environment variable minus the length of the key (characters before the
 * equal sign).
 * 5: Compare the string with the current environment variable using
 * `ft_strncmp`.
 * 6: If a match is found, return the matching environment variable.
 * 8: If no match is found, return NULL.
 */
char	*is_env_var(char *str, char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (ft_strlen(str) == (ft_strlen(env[i])
				- ft_strlen(ft_strchr(env[i], '=')))
			&& ft_strncmp(str, env[i], ft_strlen(str)) == 0)
			return (env[i]);
		i++;
	}
	return (NULL);
}
