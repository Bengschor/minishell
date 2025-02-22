/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschor <bschor@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 16:08:23 by bschor            #+#    #+#             */
/*   Updated: 2024/07/24 16:23:31 by bschor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"

int	check_unset_argv(char **argv, int *c, int *save)
{
	int	i;
	int	j;
	int	res;

	i = 0;
	res = 0;
	while (argv[i])
	{
		j = 0;
		while (argv[i][j])
		{
			if (!(ft_isalnum(argv[i][j]) || argv[i][j] == 95))
			{
				res = ft_check_syntax(argv[i][j], c, res);
				if (res == 1)
					*save = i;
			}
			j++;
		}
		i++;
	}
	return (res);
}

void	remove_elem(char **argv, t_env **env)
{
	int	i;

	i = -1;
	while (argv[++i])
	{
		if (if_same_word(argv[i], "_"))
			continue ;
		in_unset_env(argv[i], env);
	}
}

int	do_unset(char **argv, t_env **env)
{
	int	res;
	int	c;
	int	i;

	c = 0;
	i = 0;
	res = check_unset_argv(argv, &c, &i);
	if (res == 1)
		printf("minishell: unset: `%s': not a valid identifier\n", argv[i]);
	else if (res == 2)
		printf("minishell: syntax error near unexpected token `%c'\n", c);
	else
		remove_elem(argv, env);
	return (0);
}
