/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschor <bschor@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 18:00:21 by bschor            #+#    #+#             */
/*   Updated: 2024/07/24 14:46:11 by bschor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"

char	*get_key(char *key_value)
{
	char	*key;
	int		i;

	if (!key_value)
		return (NULL);
	i = 0;
	while (key_value[i] && key_value[i] != '=')
		i++;
	key = malloc(i * sizeof(char) + 1);
	if (!key)
		return (NULL);
	i = 0;
	while (key_value[i] && key_value[i] != '=')
	{
		key[i] = key_value[i];
		i++;
	}
	key[i] = '\0';
	return (key);
}

char	*ft_getenv(char *key, t_env **env)
{
	char	*curr_key;
	t_env	*curr;

	curr = *env;
	while (curr)
	{
		curr_key = get_key(curr->key_value);
		if (if_same_word(curr_key, key))
		{
			free(curr_key);
			return (ft_strchr(curr->key_value, '=') + 1);
		}
		free(curr_key);
		curr = curr->next;
	}
	return (NULL);
}

t_env	*ft_super_getenv(char *key, t_env **env)
{
	char	*curr_key;
	t_env	*curr;

	curr = *env;
	while (curr)
	{
		curr_key = get_key(curr->key_value);
		if (!curr_key)
			return (NULL);
		if (if_same_word(curr_key, key))
		{
			free(curr_key);
			return (curr);
		}
		free(curr_key);
		curr = curr->next;
	}
	return (NULL);
}

void	add_elem(t_env **env, char *envp, int *count, t_system *systm)
{
	char	*s;
	char	*key;

	key = get_key(envp);
	if (!key)
		return ;
	if (if_same_word(key, "SHLVL"))
	{
		*count = 1;
		s = check_shlvl(envp);
		key = ft_realloc(key, s, systm);
		if (!key)
			return ;
		free(s);
		ft_lstadd_back(env, ft_lstnew(key));
	}
	else if (*count == 0 && if_same_word(key, "_"))
	{
		ft_lstadd_back(env, ft_lstnew("SHLVL=1"));
		ft_lstadd_back(env, ft_lstnew(envp));
	}
	else if (!if_same_word(key, "OLDPWD"))
		ft_lstadd_back(env, ft_lstnew(envp));
	free(key);
}
