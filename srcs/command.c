/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkhattab <wkhattab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 18:15:06 by bschor            #+#    #+#             */
/*   Updated: 2024/06/04 18:38:35 by wkhattab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"

int	is_builtins(char *cmd)
{
	if (if_same_word(cmd, "pwd"))
		return (1);
	else if (if_same_word(cmd, "echo"))
		return (1);
	else if (if_same_word(cmd, "cd"))
		return (1);
	else if (if_same_word(cmd, "env"))
		return (1);
	else if (if_same_word(cmd, "exit"))
		return (1);
	else if (if_same_word(cmd, "export"))
		return (1);
	else if (if_same_word(cmd, "unset"))
		return (1);
	return (0);
}

int	get_argc(char **strs)
{
	int	i;

	i = 0;
	while (strs[i])
		i++;
	return (i);
}

int	do_builtins(t_system *systm, char **argv)
{
	int	argc;

	argc = get_argc(argv);
	if (if_same_word(argv[0], "pwd"))
		systm->status = do_pwd(systm);
	else if (if_same_word(argv[0], "echo"))
		systm->status = do_echo(argc, argv);
	else if (if_same_word(argv[0], "cd"))
		systm->status = do_cd(argv[1], systm);
	else if (if_same_word(argv[0], "env"))
		systm->status = do_env(argc, argv, systm->env);
	else if (if_same_word(argv[0], "exit"))
		systm->status = do_exit(argc, argv, systm);
	else if (if_same_word(argv[0], "export"))
		systm->status = do_export(argv, systm->env);
	else if (if_same_word(argv[0], "unset"))
		systm->status = do_unset(argv, systm->env);
	else if (argv[0])
		return (systm->status);
	return (systm->status);
}
