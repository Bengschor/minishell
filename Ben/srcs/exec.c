/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschor <bschor@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 17:20:39 by bschor            #+#    #+#             */
/*   Updated: 2024/05/16 13:12:09 by bschor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"

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
	int	i;

	i = 0;
	stdin2 = dup(STDIN_FILENO);
	stdout2 = dup(STDOUT_FILENO);
	while (systm->parser[i].strs)
	{
		systm->parser[i].path = get_path(systm->parser[i].strs[0], systm);
		ft_pipex(systm, i, stdout2);
		i++;
	}
	dup2(STDOUT_FILENO, stdout2);
	dup2(STDIN_FILENO, stdin2);
	close(stdout2);
	close(stdin2);
	waitpid(systm->pid, &(systm->status), 0);
	// ft_suppress_output();
	// glbl signal
	ft_wait_all(systm);
	return (0);
}