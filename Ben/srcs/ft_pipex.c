/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipex.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschor <bschor@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 08:55:35 by bschor            #+#    #+#             */
/*   Updated: 2024/05/22 10:58:18 by bschor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"

void	ft_child(int fd[2], t_system *systm, int pars_i)
{
	close(fd[1]);
	close(fd[0]);
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	if (systm->parser[pars_i].infile < 0 || systm->parser[pars_i].outfile < 0)
		exit (1);
	if (is_builtins(systm->parser[pars_i].path))
		do_builtins(systm, systm->parser[pars_i].strs);
	else
		if (execve(systm->parser[pars_i].path, systm->parser[pars_i].strs, systm->env))
			exit (systm->status);
}

int	ft_parent(int fd[2], t_system *systm, int pars_i)
{
	//signal
	signal(SIGINT, print_nl);
	signal(SIGQUIT, ft_handle_sigquit);
	close(fd[1]);
	if (systm->parser[pars_i + 1].infile <= 2)
		dup2(fd[0], STDIN_FILENO);
	close(fd[0]);
	return (0);
}

int	ft_pipex(t_system *systm, int pars_i, int stdout2)
{
	int	fd[2];

	if (pipe(fd) == -1)
		ft_crash(systm);
	if (!systm->parser[pars_i + 1].last)
		dup2(fd[1], STDOUT_FILENO);
	else
		dup2(stdout2, STDOUT_FILENO);
	if (systm->parser[pars_i].infile > 2)
		dup2(systm->parser[pars_i].infile, STDIN_FILENO);
	if (systm->parser[pars_i].outfile > 2)
		dup2(systm->parser[pars_i].outfile, STDOUT_FILENO);
	systm->pid = fork();
	if (systm->pid < 0)
		ft_crash(systm);
	if (systm->pid == 0)
		ft_child(fd, systm, pars_i);
	else
		ft_parent(fd, systm, pars_i);
	return (0);
}
