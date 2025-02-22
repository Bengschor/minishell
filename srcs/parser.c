/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschor <bschor@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 13:09:17 by bschor            #+#    #+#             */
/*   Updated: 2024/07/24 18:56:28 by bschor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"

static int	redirect(t_system *systm, int exec_i, int token)
{
	int	fd;

	systm->lexer = systm->lexer->next;
	if (token == INTO)
		fd = open(systm->lexer->str, O_RDONLY);
	if (token == OUTTO)
		fd = open(systm->lexer->str, O_WRONLY | O_CREAT | O_TRUNC, 00777);
	if (token == APPEND)
		fd = open(systm->lexer->str, O_WRONLY | O_CREAT | O_APPEND, 0777);
	if (fd == -1)
	{
		systm->status = 1;
		return (ft_printf_err("minishell: %s: %s\n", systm->lexer->str,
				strerror(errno)));
	}
	if (token == INTO)
		systm->parser[exec_i].infile = fd;
	else if (token == APPEND || token == OUTTO)
		systm->parser[exec_i].outfile = fd;
	return (0);
}

static void	init_parser(t_parser *parser, int max)
{
	int	i;

	i = 0;
	while (i <= max)
	{
		parser[i].infile = 0;
		parser[i].outfile = 1;
		parser[i].path = NULL;
		parser[i].strs = NULL;
		parser[i].last = 0;
		i++;
	}
	parser[i - 1].last = 1;
}

static int	format_exec(t_system *systm, int exec_i)
{
	while (systm->lexer && systm->lexer->token != PIPE)
	{
		if (systm->lexer->token == HERED)
			heredoc(systm, exec_i);
		else if (systm->lexer->token == INTO || systm->lexer->token == OUTTO
			|| systm->lexer->token == APPEND)
		{
			if (redirect(systm, exec_i, systm->lexer->token))
				return (1);
		}
		else if (!systm->lexer->token || systm->lexer->token == SQUOTE
			|| systm->lexer->token == DQUOTE)
			add_word(systm, exec_i);
		systm->lexer = systm->lexer->next;
	}
	if (systm->lexer && systm->lexer->token == PIPE)
		systm->lexer = systm->lexer->next;
	return (0);
}

int	ft_parser(t_system *systm)
{
	int		exec_size;
	int		i;
	t_lexer	*tmp;

	exec_size = count_pipes(systm->lexer);
	systm->parser = malloc(sizeof(t_parser) * (exec_size + 1));
	if (!systm->parser)
		return (free_all(systm, CRASH), 1);
	init_parser(systm->parser, exec_size);
	i = 0;
	tmp = systm->lexer;
	while (i < exec_size)
	{
		if (format_exec(systm, i))
			return (1);
		i++;
	}
	systm->lexer = tmp;
	return (0);
}
