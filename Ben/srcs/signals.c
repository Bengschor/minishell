/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschor <bschor@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 14:15:25 by bschor            #+#    #+#             */
/*   Updated: 2024/05/13 14:25:25 by bschor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"

// free termtype ?
int	init_termcap(void)
{
	char	*term_type;
	int		ret;

	term_type = getenv("TERM");
	if (!term_type)
		return (printf("TERM must be set (see 'env'). \n"));
	ret = tgetent(NULL, term_type);
	if (!ret || ret == -1)
		return (printf("Could not access the termcap database.. \n "));
		return (0);
}
