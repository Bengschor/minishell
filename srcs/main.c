/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschor <bschor@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 12:21:05 by bschor            #+#    #+#             */
/*   Updated: 2024/07/24 14:53:27 by bschor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"

int	g_status = 0;

static void	init_minishell(t_system *systm, char **envp)
{
	systm->env = malloc(sizeof(t_env *));
	*(systm->env) = NULL;
	ft_env(systm->env, envp, systm);
	printf(INTRO);
	systm->lexer = NULL;
	systm->parser = NULL;
	systm->status = 0;
	systm->mallocked_prompt = 0;
	ft_suppress_output();
	signal(SIGINT, new_prompt);
	signal(SIGQUIT, (void (*)(int))1);
}

static char	*get_prompt(char *str, t_system *systm)
{
	char	*prompt;

	prompt = readline(str);
	if (!prompt)
	{
		printf("\x1b[Aminishell$ exit\n");
		systm->status = 1;
		return (NULL);
	}
	return (prompt);
}

static int	minishell_loop(t_system *systm)
{
	while (1)
	{
		ft_free_systm(systm);
		systm->prompt = get_prompt("minishell$ ", systm);
		if (!systm->prompt)
			break ;
		if (quotes_by_pair(systm->prompt, systm, 0) || systm->prompt[0] == '\0')
			continue ;
		if (finish_by_pipe(systm->prompt) == 1)
			if (last_pipe(systm))
				continue ;
		add_history(systm->prompt);
		ft_lexer(systm);
		if (systm->lexer && check_syntax(systm))
			continue ;
		if (ft_parser(systm))
			continue ;
		execution(systm);
	}
	return (0);
}

int	main(int argc, char **argv, char *envp[])
{
	t_system	systm;

	if (argc != 1 || argv[1])
		return (ft_printf_err("program arguments are not interpreted\n"), 0);
	init_minishell(&systm, envp);
	minishell_loop(&systm);
	clear_history();
	free_all(&systm, CHILL);
	return (1);
}
