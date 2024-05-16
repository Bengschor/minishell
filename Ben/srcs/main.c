/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschor <bschor@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 12:21:05 by bschor            #+#    #+#             */
/*   Updated: 2024/05/16 13:57:59 by bschor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"

// static int	print_res(t_system *systm)
// {
// 	t_parser	*tcurrent;
// 	int			i;
// 	int			j;

// 	i = 0;
// 	j = 0;
// 	tcurrent = systm->parser;
// 	printf("--------parsing results--------\n");
// 	while (tcurrent[j].strs)
// 	{
// 		while (tcurrent[j].strs[i])
// 		{
// 			printf("%s|", tcurrent[j].strs[i]);
// 			i++;
// 		}
// 		i = 0;
// 		printf("\nfull_path: %s\n", tcurrent[j].path);
// 		printf("into: %d\noutto: %d\n", tcurrent[j].infile,
// 			tcurrent[j].outfile);
// 		j++;
// 	}
// 	return (0);
// }

static void	ft_reset_loop(t_system *systm)
{
	ft_free_systm(systm);
	// rl_replace_line("", 0);
	// rl_on_new_line();
	// rl_redisplay();
}

static char	*get_prompt(char *str, t_system *systm)
{
	char	*prompt;
	// rl_on_new_line();
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
		ft_reset_loop(systm);
		systm->prompt = get_prompt("minishell$ ", systm);
		if (!systm->prompt)
			break ;
		if (quotes_by_pair(systm->prompt, systm) || systm->prompt[0] == '\0')
			continue ;
		if (finish_by_pipe(systm->prompt))
			if (last_pipe(systm))
				continue ;
		add_history(systm->prompt);
		ft_lexer(systm);
		if (systm->lexer && check_syntax(systm))
			continue ;
		ft_parser(systm);
		execution(systm);
		// print_res(systm);
	}
	return (0);
}

int	main(int argc, char **argv, char *envp[])
{
	t_system	systm;

	if (argc != 1 || argv[1])
		return (printf("program arguments are not interpreted\n"), 0);
	systm.env = envp;
	systm.lexer = NULL;
	systm.parser = NULL;
	// init_termcap();
	ft_suppress_output();
	signal(SIGINT, new_prompt);
	signal(SIGQUIT, (void (*)(int))1);
	minishell_loop(&systm);
	clear_history();
	ft_crash(&systm);
	return (systm.status);
}
