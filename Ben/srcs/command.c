/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschor <bschor@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 18:15:06 by bschor            #+#    #+#             */
/*   Updated: 2024/05/16 18:15:08 by bschor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"

int is_builtins(char *cmd)
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
int get_argc(char **strs)
{
	int i;

	i = 0;
	while (strs[i])
		i++;
	return (i);
}

int do_builtins(t_system *systm, char **argv)
{
	int argc;

	argc = get_argc(argv);
	if (if_same_word(argv[0], "pwd"))
        do_pwd(argc);
    else if (if_same_word(argv[0], "echo"))
        do_echo(argc, argv);
    else if (if_same_word(argv[0], "cd"))
        do_cd(argv[1], systm);
    else if (if_same_word(argv[0], "env"))
        do_env(argc, systm->env);
    else if (if_same_word(argv[0], "exit"))
        do_exit();
    else if (if_same_word(argv[0], "export"))
        do_export(argc, argv, &systm->env);
    // else if (if_same_word(argv[0], "unset"))
    //     do_unset(argv, argc, systm->env);
    else if (argv[0])
        return (0);
	return (1);
}
