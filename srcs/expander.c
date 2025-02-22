/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschor <bschor@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 10:51:52 by bschor            #+#    #+#             */
/*   Updated: 2024/07/24 18:55:06 by bschor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"

static int	exp_env_var(char **str, int i, t_system *systm)
{
	char	*to_exp;
	char	*env_var;
	int		env_var_len;

	to_exp = ft_substr(*str, i + 1, find_next_alnum((*str) + i + 1));
	if (!to_exp)
		return (free_all(systm, CRASH), 1);
	env_var = ft_strchr(is_env_var(to_exp, systm->env), '=');
	if (env_var)
		env_var++;
	if (ft_strrpl(str, i, ft_strlen(to_exp) + 1, env_var))
		return (free_all(systm, CRASH), -10000000);
	env_var_len = ft_strlen(env_var);
	free(to_exp);
	return (env_var_len);
}

static int	exp_exit_status(int i, char **str, t_system *systm)
{
	char	*nbr_string;
	int		len_nbr;

	nbr_string = ft_itoa(systm->status);
	if (!nbr_string)
		return (free_all(systm, CRASH), -10000000);
	if (ft_strrpl(str, i, 2, nbr_string))
		return (free_all(systm, CRASH), -10000000);
	len_nbr = ft_strlen(nbr_string);
	free(nbr_string);
	return (len_nbr);
}

void	expand_str(char **str, t_system *systm)
{
	int	i;

	i = 0;
	while (i >= 0 && (*str)[i])
	{
		if ((*str)[i] == '$' && (*str)[i + 1] == '?')
			i = i + exp_exit_status(i, str, systm);
		else if (i >= 0 && (*str)[i] == '$'
			&& (!ft_isalnum((*str)[i + 1]) || (*str)[i + 1] == '_'))
			i++;
		else if (i >= 0 && (*str)[i] == '$')
			i += exp_env_var(str, i, systm);
		else
			i++;
	}
}

void	expander(t_system *systm)
{
	t_lexer	*current;

	current = systm->lexer;
	while (current)
	{
		if (current->str && (current->token == DQUOTE || !current->token))
			expand_str(&(current->str), systm);
		current = current->next;
	}
}
