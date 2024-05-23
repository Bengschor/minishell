/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschor <bschor@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 16:14:25 by bschor            #+#    #+#             */
/*   Updated: 2024/05/23 11:41:48 by bschor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"

int	ft_print_syntax(char *str, t_system *systm)
{
	systm->status = 258;
	if (str)
		ft_printf_err(str);
	return (1);
}

/**
 * @brief Converts a token character to its corresponding string 
 * representation.
 * 
 * @param token The token character.
 * @return The string representation of the token, or NULL if invalid.
 * @line by line:
 * 1-5: Checks the token character and returns the corresponding string 
 * representation.
 */
char	*tkntostr(int token)
{
	if (token == '#')
		return (">>");
	else if (token == '=')
		return ("<<");
	else if (token == '<')
		return ("<");
	else if (token == '>')
		return (">");
	else if (token == '|')
		return ("|");
	return (NULL);
}

static int	get_cmd(char *prompt, int p[2], t_system *systm)
{
	char	*tmp_prompt;

	close(p[0]);
	tmp_prompt = readline("> ");
	if (!tmp_prompt)
		return (ft_putstr_fd(prompt, p[1]), close(p[1]), ft_print_syntax("\x1b[1A\x1b[2Cminishell: syntax error: unexpected end of file\n", systm));
	else if (tmp_prompt[0] != '\0')
		tmp_prompt = ft_strjoin_free(ft_strdup(" "), tmp_prompt);
	prompt = ft_strjoin_free(prompt, tmp_prompt);
	while (ft_isallspace(tmp_prompt) || finish_by_pipe(prompt))
	{
		tmp_prompt = readline("> ");
		if (!tmp_prompt)
			return (ft_putstr_fd(prompt, p[1]), close(p[1]), ft_print_syntax("\x1b[1A\x1b[2Cminishell: syntax error: unexpected end of file\n", systm));
		else if (tmp_prompt[0] != '\0')
			tmp_prompt = ft_strjoin_free(ft_strdup(" "), tmp_prompt);
		prompt = ft_strjoin_free(prompt, tmp_prompt);
	}
	ft_putstr_fd(prompt, p[1]);
	close(p[1]);
	exit (0);
}

static void	handle_cmd(t_system *systm, int p[2])
{
	char	buffer[1024];

	close(p[1]);
	if (g_status == SIGINT)
		systm->status = 1;
	signal(SIGINT, new_prompt);
	ft_bzero(buffer, 1024);
	read(p[0], buffer, 1023);
	systm->prompt = ft_strdup(buffer);
	close(p[0]);

}

int	last_pipe(t_system *systm)
{
	int		pid;
	int		p[2];

	pipe(p);
	signal(SIGINT, print_nl);
	pid = fork();
	if (pid < 0)
		return (ft_crash(systm), 1);
	if (pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		get_cmd(systm->prompt, p, systm);
		exit(0);
	}
	else
	{
		waitpid(pid, NULL, 0);
		handle_cmd(systm, p);
	}
	if (g_status == SIGINT)
		return (1);
	return (0);
}
