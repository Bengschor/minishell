/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschor <bschor@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 12:21:05 by bschor            #+#    #+#             */
/*   Updated: 2024/05/10 14:30:15 by bschor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"

static int	print_res(t_system *systm)
{
	t_parser	*tcurrent;
	int			i;
	int			j;

	i = 0;
	j = 0;
	tcurrent = systm->parser;
	while (tcurrent[j].strs)
	{
		while (tcurrent[j].strs[i])
		{
			printf("%s|", tcurrent[j].strs[i]);
			i++;
		}
		i = 0;
		printf("\ninto: %d\noutto: %d\n", tcurrent[j].infile,
			tcurrent[j].outfile);
		j++;
	}
	return (0);
}

static char	*get_prompt(char *str)
{
	char	*prompt;

	prompt = readline(str);
	if (!*prompt)
		return (prompt);
	add_history(prompt);
	return (prompt);
}

static int	minishell_loop(t_system *systm)
{
	while (1)
	{
		ft_crash(systm);
		systm->prompt = get_prompt("minishell$ ");
		if (quotes_by_pair(systm->prompt))
			continue ;
		ft_lexer(systm);
		if (systm->lexer && check_syntax(systm))
			continue ;
		ft_parser(systm);
		print_res(systm);
	}
}

int	main(int argc, char **argv, char *envp[])
{
	t_system	systm;

	if (argc != 1 || argv[1])
		printf("program arguments are not interpreted\n");
	systm.env = envp;
	systm.lexer = NULL;
	systm.parser = NULL;
	minishell_loop(&systm);
	ft_crash(&systm);
}