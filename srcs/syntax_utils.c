/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschor <bschor@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 16:14:25 by bschor            #+#    #+#             */
/*   Updated: 2024/07/24 18:56:37 by bschor           ###   ########.fr       */
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
		return (ft_putstr_fd(prompt, p[1]), close(p[1]),
			ft_print_syntax(UNXEOF, systm));
	else if (tmp_prompt[0] != '\0')
		tmp_prompt = ft_strjoin_free(ft_strdup(" "), tmp_prompt);
	prompt = ft_strjoin_free(prompt, tmp_prompt);
	while (ft_isallspace(tmp_prompt) || finish_by_pipe(prompt))
	{
		free(tmp_prompt);
		tmp_prompt = readline("> ");
		if (!tmp_prompt)
			return (ft_putstr_fd(prompt, p[1]), close(p[1]),
				ft_print_syntax(UNXEOF, systm));
		else if (tmp_prompt[0] != '\0')
			tmp_prompt = ft_strjoin_free(ft_strdup(" "), tmp_prompt);
		prompt = ft_strjoin_free(prompt, tmp_prompt);
	}
	free(tmp_prompt);
	ft_putstr_fd(prompt, p[1]);
	free(prompt);
	return (close(p[1]));
}

static void	handle_cmd(t_system *systm, int p[2])
{
	char	*buffer;

	close(p[1]);
	if (g_status == SIGINT)
		systm->status = 1;
	signal(SIGINT, new_prompt);
	buffer = readstr(p[0]);
	systm->prompt = buffer;
	systm->mallocked_prompt = 1;
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
		return (free_all(systm, CRASH), 1);
	if (pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		get_cmd(systm->prompt, p, systm);
		free_all(systm, CHILL);
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
