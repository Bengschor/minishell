/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschor <bschor@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 10:14:11 by bschor            #+#    #+#             */
/*   Updated: 2024/07/24 18:55:31 by bschor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"

static int	get_strings(t_system *systm, char *key, int p[2], int heredoc_type)
{
	char	*buffer;

	close(p[0]);
	buffer = readline("> ");
	if (!buffer)
		return (close(p[1]));
	while (ft_strcmp(buffer, key))
	{
		if (!heredoc_type)
			expand_str(&buffer, systm);
		ft_putstr_fd(buffer, p[1]);
		ft_putstr_fd("\n", p[1]);
		free(buffer);
		buffer = readline("> ");
		if (!buffer)
			return (close(p[1]));
	}
	free(buffer);
	close(p[1]);
	return (0);
}

static int	handle_strings(t_system *systm, int exec_i, int p[2])
{
	close(p[1]);
	if (g_status == SIGINT)
		systm->status = 1;
	signal(SIGINT, new_prompt);
	if (systm->parser[exec_i].infile > 2)
		close(systm->parser[exec_i].infile);
	if (systm->parser[exec_i].infile >= 0)
		systm->parser[exec_i].infile = p[0];
	return (0);
}

int	heredoc(t_system *systm, int exec_i)
{
	int		heredoc_type;
	int		pid;
	int		p[2];

	systm->lexer = systm->lexer->next;
	heredoc_type = systm->lexer->token;
	signal(SIGINT, update_glob);
	pipe(p);
	pid = fork();
	if (pid < 0)
		return (free_all(systm, CRASH), 1);
	if (pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		get_strings(systm, systm->lexer->str, p, heredoc_type);
		free_all(systm, CHILL);
		exit(0);
	}
	else
	{
		waitpid(pid, NULL, 0);
		handle_strings(systm, exec_i, p);
	}
	return (0);
}
