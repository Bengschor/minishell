/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschor <bschor@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 09:55:46 by bschor            #+#    #+#             */
/*   Updated: 2024/04/27 15:32:26 by bschor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"

/**
 * @brief adds a new element to the list with all the data received
 * 
 * @param systm A pointer to the system struct.
 * @param str The string content of the node.
 * @param token The token associated with the node.
 * @return 0 on success, 1 on failure.
 * @line by line:
 * Allocates memory for a new lexer node.
 * Sets attributes of the new node.
 * Inserts the new node into the lexer linked list.
 */
static int	add_lexer(t_system *systm, char *str, int token)
{
	t_lexer	*new;
	t_lexer	*current;

	new = malloc(sizeof(t_lexer));
	if (!new)
		return (free(str), ft_crash(systm), 1);
	new->str = str;
	new->token = token;
	new->next = NULL;
	if (systm->lexer == NULL)
	{
		systm->lexer = new;
		new->prev = NULL;
		return (0);
	}
	current = systm->lexer;
	while (current->next)
		current = current->next;
	current->next = new;
	new->prev = current;
	return (0);
}

/**
 * @brief joins words and quotes no separated by spaces and puts 
keeps them in quoted token (for the heredoc)
 * 
 * @param systm A pointer to the system struct.
 * @return 0 on success, 1 on failure.
 * @line by line:
 * Iterates through the lexer nodes.
 * Checks if adjacent nodes are words without spaces in between.
 * Joins adjacent nodes if there are no spaces in the words and the
 * adjacent node is quoted.
 */
int	join_words(t_system *systm)
{
	t_lexer	*current;

	current = systm->lexer;
	while (current && current->next)
	{
		if ((current->token == DQUOTE || current->token == SQUOTE
				|| (!current->token && !ft_strchr(current->str, ' ')))
			&& (current->next->token == DQUOTE
				|| current->next->token == SQUOTE
				|| (!current->next->token
					&& !ft_strchr(current->next->str, ' '))))
		{
			if (!ft_nodjoin(current, current->next))
				return (ft_crash(systm), 1);
		}
		current = current->next;
	}
	return (0);
}

/**
 * @brief Trims whitespace from lexer nodes and deletes empty nodes.
 * 
 * @param systm A pointer to the system struct.
 * @return 0 on success, 1 on failure.
 * @line by line:
 * Initializes variables.
 * Handles special case of leading whitespace.
 * Iterates through lexer nodes, trims whitespace, and deletes empty nodes.
 * Trims whitespace from the string.
 * Deletes empty nodes.
 */
int	ft_lextrim(t_system *systm)
{
	t_lexer	*current;
	char	*tmp;

	current = systm->lexer;
	if (current && !current->token && ft_isallspace(current->str))
		systm->lexer = systm->lexer->next;
	while (current)
	{
		if (current->str && !current->token)
		{
			tmp = ft_strtrim(current->str, "\t\n ");
			if (!tmp)
				return (ft_crash(systm), 1);
			free(current->str);
			current->str = tmp;
		}
		if (!current->token && ft_isallspace(current->str))
			del_node(&current);
		else
			current = current->next;
	}
	return (0);
}

/**
 * @brief creates a chained list of the strings and tokens, also handling
the quotes but keeping a trace of them in case of an expension later
Tokens have a null string and strings have a null token except quotes
 * 
 * @param systm A pointer to the system struct.
 * @line by line:
 * Iterates through the prompt string.
 * Calls appropriate handlers based on encountered characters.
 * Calls the expander function.
 * Calls functions to join words and trim lexer nodes.
 */
void	ft_lexer(t_system	*systm)
{
	int	i;

	i = 0;
	while (systm->prompt[i])
	{
		if (systm->prompt[i] == SQUOTE)
			add_lexer(systm, handle_quote(systm, &i), SQUOTE);
		else if (systm->prompt[i] == DQUOTE)
			add_lexer(systm, handle_quote(systm, &i), DQUOTE);
		else if ((systm->prompt[i] == PIPE) || (systm->prompt[i] == INTO)
			|| (systm->prompt[i] == OUTTO))
			add_lexer(systm, NULL, handle_token(systm, &i));
		else
			add_lexer(systm, handle_word(systm, &i), 0);
		i++;
	}
	expander(systm);
	join_words(systm);
	ft_lextrim(systm);
}

/*
main to test my part
*/
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
	systm.prompt = "test rtyui |  | 53 6543 -5";
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
