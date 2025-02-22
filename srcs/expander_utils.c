/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschor <bschor@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 15:01:18 by bschor            #+#    #+#             */
/*   Updated: 2024/07/24 18:54:55 by bschor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"

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

int	find_next_alnum(char *str)
{
	int	i;

	i = 0;
	while (str[i] && (ft_isalnum(str[i]) || str[i] == '_'))
		i++;
	return (i);
}

char	*is_env_var(char *str, t_env **env)
{
	t_env	*curr;

	curr = *env;
	while (curr)
	{
		if (ft_strlen(str) == (ft_strlen(curr->key_value)
				- ft_strlen(ft_strchr(curr->key_value, '=')))
			&& ft_strncmp(str, curr->key_value, ft_strlen(str)) == 0)
			return (curr->key_value);
		curr = curr->next;
	}
	return (NULL);
}
