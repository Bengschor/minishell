/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschor <bschor@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 16:08:23 by bschor            #+#    #+#             */
/*   Updated: 2024/07/24 18:56:45 by bschor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"

int	finish_by_pipe(char *str)
{
	int	i;

	i = ft_strlen(str) - 1;
	while (i > 0 && ft_isspace(str[i]))
		i--;
	if (i != 0 && str[i] == '|')
	{
		while (--i > 0 && ft_isspace(str[i]))
			;
		if (ft_strchr("<|>", str[i]))
			return (0);
		else
			return (1);
	}
	return (0);
}

int	quotes_by_pair(char *str, t_system *systm, int i)
{
	while (str[i])
	{
		if ((str[i] == SQUOTE || str[i] == DQUOTE) && !str[i + 1])
			return (add_history(systm->prompt),
				ft_print_syntax(UNCQUO, systm));
		if (str[i] == SQUOTE)
		{
			while (str[++i] && str[i] != SQUOTE)
				;
			if (!str[i] && str[i - 1] != SQUOTE)
				return (add_history(systm->prompt),
					ft_print_syntax(UNCQUO, systm));
		}
		if (str[i] == DQUOTE)
		{
			while (str[++i] && str[i] != DQUOTE)
				;
			if (!str[i] && str[i - 1] != DQUOTE)
				return (add_history(systm->prompt),
					ft_print_syntax(UNCQUO, systm));
		}
		i++;
	}
	return (EXIT_SUCCESS);
}

int	check_syntax(t_system *systm)
{
	t_lexer	*cur;

	cur = systm->lexer;
	if (cur->token == PIPE)
		return (ft_printf_err(TKNSTX, cur->token),
			ft_print_syntax(NULL, systm));
	while (cur->next)
	{
		if ((cur->token && cur->next->token) && (ft_strchr("#=<>", cur->token)
				&& ft_strchr("#=<>|", cur->next->token)))
			return (ft_printf_err(TKNSSTX, tkntostr(cur->next->token)),
				ft_print_syntax(NULL, systm));
		cur = cur->next;
	}
	if (cur->token == HERED || cur->token == APPEND || cur->token == INTO
		|| cur->token == OUTTO)
		return (ft_print_syntax(NLSTX, systm));
	return (0);
}
