/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschor <bschor@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 16:14:25 by bschor            #+#    #+#             */
/*   Updated: 2024/07/24 15:55:32 by bschor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"

int	is_syntax(int c)
{
	if (c == 40 || c == 41 || c == 91 || c == 93
		|| c == 123 || c == 124 || c == 38
		|| c == 62 || c == 60 || c == 59)
		return (1);
	return (0);
}

int	is_id_invalid(int c)
{
	if (c == 35 || c == 64 || c == 126 || c == 33
		|| c == 37 || c == 42 || c == 0x3f || c == 0x3d
		|| c == 0x24 || c == 0x26 || c == 45)
		return (1);
	return (0);
}

int	ft_check_syntax(char s, int *c, int res)
{
	if (is_syntax(s))
	{
		*c = (int)s;
		return (2);
	}
	else if (is_id_invalid(s) && res != 2)
		return (1);
	return (res);
}

void	ft_lstdelone(t_env *curr, t_env **env)
{
	t_env	*prev;
	t_env	*next;

	prev = *env;
	next = curr->next;
	while (prev)
	{
		if (if_same_word(curr->key_value, prev->next->key_value))
		{
			prev->next = next;
			free(curr->key_value);
			free(curr);
			return ;
		}
		prev = prev->next;
	}
}

int	in_unset_env(char *key, t_env **env)
{
	t_env	*curr;
	t_env	*next;
	char	*key_curr;

	curr = *env;
	while (curr)
	{
		next = curr->next;
		key_curr = ft_substr(curr->key_value, 0, get_pos(curr->key_value, '='));
		if (if_same_word(key_curr, key))
		{
			ft_lstdelone(curr, env);
			free(key_curr);
			return (1);
		}
		free(key_curr);
		curr = next;
	}
	return (0);
}
