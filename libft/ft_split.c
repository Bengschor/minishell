/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschor <bschor@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 14:36:01 by bschor            #+#    #+#             */
/*   Updated: 2023/10/19 18:26:22 by bschor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_word_count(const char *str, char c)
{
	int	i;
	int	word;

	i = 0;
	word = 0;
	if (str == NULL)
		return (-1);
	while (str[i])
	{
		while (str[i] == c && str[i])
			i++;
		if (str[i] != 0)
			word++;
		while (str[i] != c && str[i])
			i++;
	}
	return (word);
}

int	ft_free(char **tab, int tab_index)
{
	int	i;

	i = 0;
	while (i < tab_index)
	{
		free(tab[i]);
		i++;
	}
	free(tab);
	return (-1);
}

int	ft_init(const char *str, char c, char **tab, int tab_index)
{
	int	i;
	int	len;

	len = 0;
	i = 0;
	while (str && str[i] != 0)
	{
		while (str[i] == c && str[i])
			i++;
		while (str[i] != c && str[i])
		{
			i++;
			len++;
		}
		if (len > 0)
		{
			tab[tab_index] = malloc(sizeof(char) * (len + 1));
			tab[++tab_index] = NULL;
			if (!tab[tab_index - 1])
				return (ft_free(tab, tab_index));
			len = 0;
		}
	}
	tab[tab_index] = NULL;
	return (tab_index);
}

char	**ft_split_two(char const *str, char c, int i, int j)
{
	char	**tab;
	int		tab_index;

	tab_index = 0;
	tab = malloc(sizeof(char *) * (ft_word_count(str, c) + 1));
	if (tab == NULL || str == NULL)
		return (NULL);
	if (ft_init(str, c, tab, tab_index) == -1)
		return (NULL);
	while (str[i] && tab[tab_index])
	{
		while (str[i] == c && str[i])
			i++;
		while (str[i] != c && str[i])
		{
			tab[tab_index][j++] = str[i++];
			tab[tab_index][j] = 0;
		}
		tab_index++;
		j = 0;
	}
	return (tab);
}

char	**ft_split(char const *str, char c)
{
	int		i;
	int		j;

	j = 0;
	i = 0;
	return (ft_split_two(str, c, i, j));
}
