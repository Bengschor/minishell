/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschor <bschor@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 13:09:17 by bschor            #+#    #+#             */
/*   Updated: 2024/04/26 19:40:42 by bschor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"

/*
what if there already is a fd ?
*/
/**
 * @brief Redirects input or output according to the given token.
 * 
 * @param systm A pointer to the system struct.
 * @param exec_i The index of the current command.
 * @param token The token representing the type of redirection.
 * @return 0 on success, a non-zero value on failure.
 * @line by line:
 * 1: Move to the next token in the lexer linked list.
 * 2-9: Open the file for reading (O_RDONLY) if the token is INTO.
 * 10-17: Open the file for writing (O_WRONLY | O_CREAT | O_TRUNC) if the token is OUTTO.
 * 18-25: Open the file for appending (O_WRONLY | O_CREAT | O_APPEND) if the token is APPEND.
 * 26-30: Handle file opening errors and update the file descriptor in the parser array.
 * 31: Return 0 on success.
 */
static int	redirect(t_system *systm, int exec_i, int token)
{
	int	fd;

	systm->lexer = systm->lexer->next;
	if (token == INTO)
		fd = open(systm->lexer->str, O_RDONLY);
	if (token == OUTTO)
		fd = open(systm->lexer->str, O_WRONLY | O_CREAT | O_TRUNC,  00777);
	if (token == APPEND)
		fd = open(systm->lexer->str, O_WRONLY | O_CREAT | O_APPEND, 0777);
	if (fd == -1)
		return (printf("ERROR OPENING FILE")); // mettre perror je pense
	if (token == INTO)
		systm->parser[exec_i].infile = fd;
	else if (token == APPEND || token == OUTTO)
		systm->parser[exec_i].outfile = fd;
	return (0);
}

/**
 * @brief Initializes the parser array with default values.
 * 
 * @param parser The parser array to be initialized.
 * @param max The maximum index of the parser array.
 * @line by line:
 * 1-8: Iterate over the parser array and initialize each element with default values.
 */
static void	init_parser(t_parser *parser, int max)
{
	int	i;

	i = 0;
	while (i <= max)
	{
		parser[i].infile = 0;
		parser[i].outfile = 1;
		parser[i].path = NULL;
		parser[i].strs = NULL;
		i++;
	}
}

/**
 * @brief Formats the execution of a command.
 * 
 * @param systm A pointer to the system struct.
 * @param exec_i The index of the current command.
 * @return 0 on success.
 * @line by line:
 * 1-19: Iterate over the lexer linked list until a pipe token is encountered.
 * 2-8: Handle heredoc token, redirection tokens, and add words to the parser array.
 * 9-12: Move to the next node in the lexer linked list if a pipe token is encountered.
 */
static int	format_exec(t_system *systm, int exec_i)
{
	while (systm->lexer && systm->lexer->token != PIPE)
	{
		if (systm->lexer->token == HERED)
			heredoc(systm, exec_i);
		else if (systm->lexer->token == INTO || systm->lexer->token == OUTTO
			|| systm->lexer->token == APPEND)
			redirect(systm, exec_i, systm->lexer->token);
		else if (!systm->lexer->token || systm->lexer->token == SQUOTE
			|| systm->lexer->token == DQUOTE)
			add_word(systm, exec_i);
		systm->lexer = systm->lexer->next;
	}
	if (systm->lexer && systm->lexer->token == PIPE)
		systm->lexer = systm->lexer->next;
	return (0);
}

/**
 * @brief Parses the lexer linked list into commands and redirections.
 * 
 * @param systm A pointer to the system struct.
 * @return 0 on success, a non-zero value on failure.
 * @line by line:
 * 1-3: Initialize the number of commands (exec_size) and the index variable i.
 * 4-6: Allocate memory for the parser array based on the number of pipes in the lexer linked list.
 * 7: Initialize the parser array with default values.
 * 8-18: Iterate over the lexer linked list and format each command and redirection.
 * 19: Return 0 on success.
 */
int	ft_parser(t_system *systm)
{
	int		exec_size;
	int		i;
	t_lexer	*tmp;

	exec_size = count_pipes(systm->lexer);
	systm->parser = malloc(sizeof(t_parser) * (exec_size + 1));
	if (!systm->parser)
		return (ft_crash(systm), 1);
	init_parser(systm->parser, exec_size);
	i = 0;
	tmp = systm->lexer;
	while (i < exec_size)
	{
		format_exec(systm, i);
		i++;
	}
	systm->lexer = tmp;
	return (0);
}
