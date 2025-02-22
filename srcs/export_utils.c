/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschor <bschor@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 17:20:39 by bschor            #+#    #+#             */
/*   Updated: 2024/05/28 15:21:34 by bschor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"

int	if_key(char *str, char *var)
{
	char	*key;
	int		i;

	i = 0;
	while (var[i] && var[i] != '=')
		i++;
	key = malloc(i * sizeof(char) + 1);
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

int	get_pos(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != c)
		i++;
	return (i);
}

char	**if_in_env(char *key_value, t_env **env)
{
	t_env	*curr;
	char	*key;

	key = ft_substr(key_value, 0, get_pos(key_value, '='));
	curr = *env;
	while (curr)
	{
		if (if_key(key, curr->key_value))
		{
			free(key);
			return (&curr->key_value);
		}
		curr = curr->next;
	}
	free(key);
	return (NULL);
}

int	ft_add_new(t_env **env, char *str)
{
	t_env	*elem;
	t_env	*curr;
	t_env	*next;
	int		i;
	int		size;

	i = 1;
	elem = ft_lstnew(str);
	size = ft_lstsize(*env);
	if (!elem)
		return (0);
	curr = *env;
	while (curr->next)
	{
		next = curr->next;
		if (i > size - 2)
		{
			curr->next = elem;
			elem->next = next;
			return (1);
		}
		curr = next;
		i++;
	}
	return (1);
}
