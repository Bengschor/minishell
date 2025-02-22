/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschor <bschor@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 18:15:15 by bschor            #+#    #+#             */
/*   Updated: 2024/05/28 13:31:53 by bschor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"

int	if_same_word(char *s1, char *s2)
{
	int	size1;
	int	size2;
	int	i;

	if (!s1 || !s2)
		return (0);
	size1 = ft_strlen(s1);
	size2 = ft_strlen(s2);
	if (size1 != size2)
		return (0);
	i = 0;
	while (s1[i])
	{
		if (s1[i] != s2[i])
			return (0);
		i++;
	}
	return (1);
}

int	if_blank(char c)
{
	if ((c <= 13 && c >= 9) || c == 32)
		return (1);
	return (0);
}

char	*ft_realloc(char *s, char *cpy, t_system *systm)
{
	char	*key;

	key = get_key(s);
	if (!key)
		return (NULL);
	free(s);
	s = ft_strjoin(key, "=");
	s = join_and_free(s, cpy, systm);
	free(key);
	if (!s)
		return (NULL);
	return (s);
}

int	if_option(char *arg)
{
	int	i;

	i = 1;
	if (!arg)
		return (0);
	if (arg[0] == '-')
	{
		while (arg[i])
		{
			if (arg[i] != 'n')
				return (0);
			i++;
		}
	}
	else
		return (0);
	return (1);
}

int	is_all_digit(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '+' || str[i] == '-')
		i++;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}
