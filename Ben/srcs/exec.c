/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschor <bschor@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 17:20:39 by bschor            #+#    #+#             */
/*   Updated: 2024/05/22 10:55:42 by bschor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"

static void	check_signal(t_system *systm)
{
	if (g_status == SIGINT)
		systm->status = 130;
	else if (g_status == SIGQUIT)
		systm->status = 131;
	else if (g_status == SIGQUIT || g_status == SIGINT)
		g_status = 0;
}

void	ft_wait_all(t_system *systm)
{
	int i;

	i = 0;
	while (systm->parser[i].strs)
	{
		wait(NULL);
		i++;
	}
}

int	execution(t_system *systm)
{
	int	stdin2;
	int	stdout2;
	int	child_status;
	int	i;

	i = 0;
	stdin2 = dup(STDIN_FILENO);
	stdout2 = dup(STDOUT_FILENO);
	ft_include_output();
	if (systm->parser[i].strs && systm->parser[i + 1].last
		&& is_builtins(systm->parser[i].strs[0]))
		do_builtins(systm, systm->parser[i++].strs);
	while (!systm->parser[i].last)
	{
		if (systm->parser[i].strs)
			systm->parser[i].path = get_path(systm->parser[i].strs[0], systm);
		ft_pipex(systm, i, stdout2);
		i++;
	}
	dup2(stdout2, STDOUT_FILENO);
	dup2(stdin2, STDIN_FILENO);
	close(stdout2);
	close(stdin2);
	waitpid(systm->pid, &child_status, 0);
	systm->status = WEXITSTATUS(child_status);
	check_signal(systm);
	ft_wait_all(systm);
	ft_suppress_output();
	signal(SIGINT, new_prompt);
	signal(SIGQUIT, (void (*)(int))1);
	return (0);
}
