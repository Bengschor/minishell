/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschor <bschor@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 17:20:39 by bschor            #+#    #+#             */
/*   Updated: 2024/05/15 18:36:48 by bschor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"

int	execution(t_system *systm)
{
	int	stdin;
	int	stdout;
	int	i;

	stdin = dup(STDIN_FILENO);
	stdout = dup(STDOUT_FILENO);
	while (systm->parser[i].strs)
	{
		systm->parser[i].path = get_path(systm, i);
		if (!systm->parser[i].path)
			return (EXIT_FAILURE); // fac | echo test ET echo test | fac pas le meme resultat
		ft_pipex(systm, i);
		i++;
	}
	waitpid(systm->pid, &(systm->status), 0);
	
}