/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschor <bschor@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 16:14:25 by bschor            #+#    #+#             */
/*   Updated: 2024/04/26 19:17:56 by bschor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"

/**
 * @brief Converts a token character to its corresponding string representation.
 * 
 * @param token The token character.
 * @return The string representation of the token, or NULL if invalid.
 * @line by line:
 * 1-5: Checks the token character and returns the corresponding string representation.
 */
char	*tkntostr(int token)
{
	if (token == '#')
		return (">>");
	else if (token == '=')
		return ("<<");
	return (NULL);
}
