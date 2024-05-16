/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschor <bschor@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 18:15:15 by bschor            #+#    #+#             */
/*   Updated: 2024/05/16 18:15:20 by bschor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"

void ch_oldpwd()
{
	char *str;
	char *str2;
	int i;

	str = getenv("OLDPWD");
	str2 = getenv("PWD");
	ft_bzero(str, ft_strlen(str));
	i = 0;
	while (str2[i])
	{
		str[i] = str2[i];
		i++;
	}
	str[i] = '\0';
}

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

int if_blank(char c)
{
	if ((c <= 13 && c >= 9 )|| c == 32)
		return (1);
	return (0);
}

char **ft_split_in_2(char *str)
{
	char **tabb;
	char *s1;
	char *s2;
	int save;
	int i;

	tabb = malloc(sizeof(char *) * 2);
	if (!tabb || !str)
		return NULL;
	i = 0;
	while (str[i] && str[i] != '=')
		i++;

	s1 = ft_substr(str, 0, i);
	if (!s1)
		return NULL;
	i++;
	save = i;
	while(str[i] && !if_blank(str[i]))
		i++;
	s2 = ft_substr(str, save, i);
	if (!s2)
	{
		free(s1);
		return NULL;
	}
	tabb[0] = s1;
	tabb[1] = s2;
	return (tabb);
}

int if_key(char *str, char *var)
{
    char *key;
    int i;

    i = 0;
    while (var[i] && var[i] != '=')
        i++;
    key = malloc(i * sizeof(char));
    key[i] = '\0';
    while (--i >= 0)
        key[i] = var[i];
    if (if_same_word(key, str))
    {
    	free(key);
        return (1);
    }
    free(key);
    return (0);
}

int ft_setenv(char *key, char *value, char ***env)
{
	char **tabb;
	int i;
	int size;
	int x;


	x = 0;
	size = 0;
	while ((*env)[size] != NULL)
		size++;
	tabb = (char **)malloc((size + 2) * sizeof(char *));
	if (!tabb)
		return (0);
	i = 0;
	while (i < size)
	{
		if (if_key(key, (*env)[i]))
		{
			tabb[i] = ft_strjoin(key, "=");
			tabb[i] = ft_strjoin(tabb[i], value);
			x = 1;
		}
		else
			tabb[i] = (*env)[i];
		i++;
	}
	if (x == 0)
	{
		tabb[i] = ft_strjoin(key, "=");
		tabb[i] = ft_strjoin(tabb[i], value);
		tabb[i + 1] = NULL;
	}
	*env = tabb;
	return (1);
}