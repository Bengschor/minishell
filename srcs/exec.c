/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschor <bschor@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 17:20:39 by bschor            #+#    #+#             */
/*   Updated: 2024/07/24 18:07:30 by bschor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"

static void	check_signal(t_system *systm)
{
	if (g_status == SIGINT)
	{
		systm->status = 130;
		ft_putchar_fd('\n', 1);
	}
	else if (g_status == SIGQUIT)
	{
		systm->status = 131;
		ft_putstr_fd("Quit: 3\n", 1);
	}
	else if (g_status == SIGQUIT || g_status == SIGINT)
		g_status = 0;
}

static void	ft_wait_all(t_system *systm)
{
	int	i;

	i = 0;
	while (systm->parser[i].strs)
	{
		wait(NULL);
		i++;
	}
}

static void	exec_loop(t_system *systm, int i)
{
	int	child_status;

	if (systm->parser[i].strs && systm->parser[i + 1].last
		&& is_builtins(systm->parser[i].strs[0]))
	{
		if (systm->parser[i].infile > 2)
			dup2(systm->parser[i].infile, STDIN_FILENO);
		if (systm->parser[i].outfile > 2)
			dup2(systm->parser[i].outfile, STDOUT_FILENO);
		do_builtins(systm, systm->parser[i++].strs);
		return ;
	}
	ft_include_output();
	while (!systm->parser[i].last)
	{
		if (systm->parser[i].strs)
			systm->parser[i].path = get_path(systm->parser[i].strs[0],
					systm, ft_getenv("PATH", systm->env));
		ft_pipex(systm, i);
		i++;
	}
	waitpid(systm->pid, &child_status, 0);
	if (systm->parser[0].strs)
		systm->status = WEXITSTATUS(child_status);
}

int	execution(t_system *systm)
{
	int	i;

	i = 0;
	systm->std[0] = dup(STDIN_FILENO);
	systm->std[1] = dup(STDOUT_FILENO);
	exec_loop(systm, i);
	dup2(systm->std[1], STDOUT_FILENO);
	dup2(systm->std[0], STDIN_FILENO);
	close(systm->std[1]);
	close(systm->std[0]);
	check_signal(systm);
	ft_wait_all(systm);
	ft_suppress_output();
	signal(SIGINT, new_prompt);
	signal(SIGQUIT, (void (*)(int))1);
	return (0);
}
