/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschor <bschor@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 14:15:25 by bschor            #+#    #+#             */
/*   Updated: 2024/05/14 10:13:30 by bschor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"

void	new_prompt(int signal)
{
	signal = 0;
	printf("\n");
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

void    ft_suppress_output(void)
{
    struct termios    new_settings;

    if (tcgetattr(0, &new_settings))
        perror("minishell: tcsetattr");
    new_settings.c_lflag &= ~ECHOCTL;
    if (tcsetattr(0, 0, &new_settings))
        perror("minishell: tcsetattr");
}

// free termtype ?
// int	init_termcap(void)
// {
// 	char	*term_type;
// 	int		ret;

// 	term_type = getenv("TERM");
// 	if (!term_type)
// 		return (printf("TERM must be set (see 'env'). \n"));
// 	ret = tgetent(NULL, term_type);
// 	if (!ret || ret == -1)
// 		return (printf("Could not access the termcap database.. \n "));
// 		return (0);
// }
