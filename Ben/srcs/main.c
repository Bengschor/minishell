/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschor <bschor@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 12:21:05 by bschor            #+#    #+#             */
/*   Updated: 2024/05/09 12:41:56 by bschor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"

int	main(void)
{
	t_system	systm;
	t_lexer		*current;
	t_parser	*tcurrent;
	int			i;
	int			j = 0;
	char		*env[] = {"test1=Ben", "test2=WAs", NULL};

	systm.env = env;
	systm.status = 4210;
	systm.prompt = "test rtyui |  53 65 -5 << test";
	i = 0;
	systm.lexer = NULL;
	if (quotes_by_pair(systm.prompt))
		return (printf("not interpreting unclosed quotes\n"));
	ft_lexer(&systm);
	if (systm.lexer && check_syntax(&systm))
		return (1);
	ft_parser(&systm);
	current = systm.lexer;
	printf("\nLEXER:\n");
	while (current)
	{
		printf("%c, |%s|\n", current->token, current->str);
		current = current->next;
	}
	tcurrent = systm.parser;
	printf("\nPARSER:\n");
	while (tcurrent[j].strs)
	{
		while (tcurrent[j].strs[i])
		{
			printf("%s|", tcurrent[j].strs[i]);
			i++;
		}
		i = 0;
		printf("\ninto: %d\noutto: %d\n", tcurrent[j].infile, tcurrent[j].outfile);
		j++;
	}
	ft_crash(&systm);
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

static int	minishell_loop(t_systm *systm)
{
	while (1)
	{
		systm->prompt = get_prompt("minishell$ ");

	}
}

int	main(int argc, char **argv, char *envp[])
{
	t_system	systm;

	if (argc != 1)
		printf("program arguments are not interpreted\n");
	systm.env = envp;
	minishell_loop(&systm);
	
}