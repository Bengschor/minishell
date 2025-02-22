/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschor <bschor@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 17:20:39 by bschor            #+#    #+#             */
/*   Updated: 2024/07/24 14:53:06 by bschor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"

int	do_export(char **argv, t_env **env)
{
	int	i;
	int	res;

	i = 1;
	if (!argv[1])
	{
		do_sort_env(env);
		return (1);
	}
	while (argv[i])
	{
		res = get_res(argv[i]);
		if (res == 0)
			printf(EXNOTVID, argv[i]);
		else if (res == 2)
			ft_setenv(argv[i], 0, env);
		else if (res == 3)
			ft_setenv(argv[i], 1, env);
		i++;
	}
	if (res == 0)
		return (1);
	return (0);
}

int	do_sort_env(t_env **env)
{
	t_env	**temp;
	t_env	*curr;
	t_env	*s;
	t_env	*elem;

	temp = malloc(sizeof(t_env));
	if (!temp)
		return (-1);
	*temp = NULL;
	curr = *env;
	while (curr)
	{
		elem = ft_lstnew(curr->key_value);
		ft_lstadd_back(temp, elem);
		curr = curr->next;
	}
	ft_lstsort(temp);
	s = *temp;
	while (s)
	{
		printf("%s\n", s->key_value);
		s = s->next;
	}
	ft_lstclear(temp);
	return (1);
}

int	get_res(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '=')
		return (0);
	while (str[i] && str[i] != '=')
	{
		if (is_syntax(str[i]) || is_id_invalid(str[i]))
			return (0);
		i++;
	}
	if (!str[i])
		return (1);
	if (str[i] == '=' && str[i + 1] == '\0')
		return (2);
	else
		return (3);
}

int	ft_setenv(char *str, int x, t_env **env)
{
	char	**key_value;
	int		y;
	char	*ptr;

	key_value = if_in_env(str, env);
	if (key_value != NULL)
	{
		if (x == 0)
		{
			y = get_pos(*key_value, '=');
			ptr = (*key_value) + y + 1;
			ft_bzero(ptr, ft_strlen(ptr));
		}
		else if (x == 1)
		{
			free(*key_value);
			*key_value = ft_strdup(str);
		}
	}
	else
		ft_add_new(env, str);
	return (1);
}
