/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschor <bschor@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 11:47:11 by bschor            #+#    #+#             */
/*   Updated: 2024/07/24 17:34:20 by bschor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"

void	free_env(t_system *systm)
{
	t_env	*curr;
	t_env	*next;

	curr = *(systm->env);
	while (curr)
	{
		next = curr->next;
		free(curr->key_value);
		free(curr);
		curr = next;
	}
	free(systm->env);
}

static void	free_lexer(t_lexer *node)
{
	t_lexer	*current;
	t_lexer	*tmp;

	while (node->prev)
		node = node->prev;
	current = node;
	while (current)
	{
		tmp = current->next;
		free(current->str);
		free(current);
		current = tmp;
	}
}

static void	free_parser(t_parser *parser)
{
	int	j;

	j = -1;
	while (!parser[++j].last)
	{
		free_strs(parser[j].strs);
		free(parser[j].path);
		if (parser[j].infile > 2)
			close(parser[j].infile);
		if (parser[j].outfile > 2)
			close(parser[j].outfile);
	}
	free_strs(parser[j].strs);
	free(parser[j].path);
	free(parser);
}

void	ft_free_systm(t_system *systm)
{
	g_status = 0;
	if (systm->lexer)
		free_lexer(systm->lexer);
	systm->lexer = NULL;
	if (systm->parser)
		free_parser(systm->parser);
	if (systm->mallocked_prompt)
		free(systm->prompt);
	systm->mallocked_prompt = 0;
	systm->parser = NULL;
}

void	free_all(t_system *systm, int flag)
{
	ft_free_systm(systm);
	if (systm->env)
		free_env(systm);
	if (flag)
	{
		printf("\033[0;31mERROR -- EXITING SAFELY\033[0m\n");
		exit (1);
	}
	return ;
}
