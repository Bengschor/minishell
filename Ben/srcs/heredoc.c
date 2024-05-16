/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschor <bschor@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 10:14:11 by bschor            #+#    #+#             */
/*   Updated: 2024/05/16 17:07:24 by bschor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"

/**
 * @brief Reads strings from standard input until a specified key is entered.
 * 
 * @param systm A pointer to the system struct.
 * @param key The key string that indicates the end of input.
 * @param p An array containing file descriptors for the pipe.
 * @param heredoc_type The type of heredoc (1 if expansion is needed,
 * 0 otherwise).
 * @return 0 on success, a non-zero value on failure.
 * @line by line:
 * 1: Declare a buffer to store input strings.
 * 2: Read input strings until the key is entered.
 * 3-10: Check if expansion is needed and expand the string accordingly.
 * 11-14: Write the string to the write end of the pipe and free the buffer.
 * 15: Close the write end of the pipe.
 * 16: Return 0 on success.
 */
static int	get_strings(t_system *systm, char *key, int p[2], int heredoc_type)
{
	char	*buffer;

	buffer = readline("> ");
	if (!buffer)
		return (printf("\x1b[1A> "), close(p[1]), ft_crash(systm), 1);
	while (ft_strcmp(buffer, key))
	{
		if (heredoc_type)
			expand_str(&buffer, systm);
		ft_putstr_fd(buffer, p[1]);
		free(buffer);
		buffer = readline("> ");
		if (!buffer)
			return (printf("\x1b[1A> "), close(p[1]), ft_crash(systm), 1);
	}
	free(buffer);
	close(p[0]);
	return (0);
}

/**
 * @brief Handles input strings received from the heredoc process.
 * 
 * @param systm A pointer to the system struct.
 * @param exec_i The index of the current command.
 * @param p An array containing file descriptors for the pipe.
 * @return 0 on success, a non-zero value on failure.
 * @line by line:
 * 1: Close the write end of the pipe.
 * 2-6: Close the input file descriptor if it's greater than 2, otherwise
 * update it.
 * 7: Return 0 on success.
 */
static int	handle_strings(t_system *systm, int exec_i, int p[2])
{
	close(p[1]);
	if (systm->parser[exec_i].infile > 2)
		close(systm->parser[exec_i].infile);
	else
		systm->parser[exec_i].infile = p[0];
	return (0);
}

/**
 * @brief Implements the heredoc functionality for input redirection.
 * 
 * @param systm A pointer to the system struct.
 * @param exec_i The index of the current command.
 * @return 0 on success, a non-zero value on failure.
 * @line by line:
 * 1: Move to the next token in the lexer linked list.
 * 2: Get the type of heredoc and create a pipe.
 * 3-8: Fork a child process to handle input strings.
 * 9-13: Child process reads input strings until the key is entered and
 * writes them to the pipe.
 * 14: Parent process waits for the child process to complete and handles
 * input strings.
 * 15: Return 0 on success.
 */
int	heredoc(t_system *systm, int exec_i)
{
	int		heredoc_type;
	int		pid;
	int		p[2];

	systm->lexer = systm->lexer->next;
	heredoc_type = systm->lexer->token;
	pipe(p);
	pid = fork();
	if (pid < 0)
		return (ft_crash(systm), 1);
	if (pid == 0)
	{
		signal(SIGINT, (void (*)(int))1);
		get_strings(systm, systm->lexer->str, p, heredoc_type);
		exit(0);
	}
	else
	{
		waitpid(pid, NULL, 0);
		handle_strings(systm, exec_i, p);
	}
	return (0);
}
