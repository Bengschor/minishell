/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipex.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschor <bschor@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 08:55:35 by bschor            #+#    #+#             */
/*   Updated: 2024/07/24 17:55:32 by bschor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"

static void	ft_clean_exit(t_system *systm, char **envp)
{
	int	i;

	i = 0;
	close(systm->std[0]);
	close(systm->std[1]);
	while (envp[i])
		free(envp[i++]);
	free(envp);
	free_all(systm, CHILL);
}

static char	**translate(t_env **env)
{
	char	**envp;
	t_env	*curr;
	int		i;

	envp = malloc(sizeof(char *) * (ft_lstsize(*env) + 1));
	if (!envp)
		return (NULL);
	*envp = NULL;
	curr = *env;
	i = 0;
	while (curr)
	{
		envp[i] = ft_strdup(curr->key_value);
		if (!envp[i])
			break ;
		curr = curr->next;
		i++;
	}
	envp[i] = NULL;
	return (envp);
}

static void	ft_child(int fd[2], t_system *systm, int pars_i)
{
	char	**envp;

	close(fd[1]);
	close(fd[0]);
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	if (systm->parser[pars_i].infile < 0 || systm->parser[pars_i].outfile < 0)
		exit (1);
	envp = translate(systm->env);
	if (is_builtins(systm->parser[pars_i].path))
		do_builtins(systm, systm->parser[pars_i].strs);
	else if (systm->parser[pars_i].path)
		execve(systm->parser[pars_i].path, systm->parser[pars_i].strs, envp);
	ft_clean_exit(systm, envp);
	exit (systm->status);
}

static int	ft_parent(int fd[2], t_system *systm, int pars_i)
{
	signal(SIGINT, update_glob);
	signal(SIGQUIT, update_glob);
	close(fd[1]);
	if (systm->parser[pars_i + 1].infile <= 2)
		dup2(fd[0], STDIN_FILENO);
	close(fd[0]);
	return (0);
}

int	ft_pipex(t_system *systm, int pars_i)
{
	int	fd[2];

	if (pipe(fd) == -1)
		free_all(systm, CRASH);
	if (!systm->parser[pars_i + 1].last)
		dup2(fd[1], STDOUT_FILENO);
	else
		dup2(systm->std[1], STDOUT_FILENO);
	if (systm->parser[pars_i].infile > 2)
		dup2(systm->parser[pars_i].infile, STDIN_FILENO);
	if (systm->parser[pars_i].outfile > 2)
		dup2(systm->parser[pars_i].outfile, STDOUT_FILENO);
	systm->pid = fork();
	if (systm->pid < 0)
		free_all(systm, CRASH);
	if (systm->pid == 0)
		ft_child(fd, systm, pars_i);
	else
		ft_parent(fd, systm, pars_i);
	return (0);
}
