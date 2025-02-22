/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschor <bschor@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 15:48:24 by bschor            #+#    #+#             */
/*   Updated: 2024/07/24 18:56:12 by bschor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"

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

static void	free_strs_crash(char **strs, int i)
{
	while (i > 0)
	{
		free(strs[i]);
		i--;
	}
	free(strs);
}

static char	**ft_addstr(char **array, char *str)
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

int	add_word(t_system *systm, int exec_i)
{
	char	**tmp;

	tmp = ft_addstr(systm->parser[exec_i].strs, systm->lexer->str);
	if (!tmp)
		return (free_all(systm, CRASH), 1);
	free_strs(systm->parser[exec_i].strs);
	systm->parser[exec_i].strs = tmp;
	return (0);
}

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
