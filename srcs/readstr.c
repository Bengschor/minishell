/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readstr.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschor <bschor@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 10:10:18 by bschor            #+#    #+#             */
/*   Updated: 2024/06/24 11:17:00 by bschor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"

static char	*ft_addchar(char *string, char c, int *len)
{
	char	*new;
	int		i;

	*len = *len + 1;
	new = malloc(sizeof(char) * *len + 1);
	if (!new)
		return (free(string), NULL);
	if (*len == 1)
	{
		new[0] = c;
		new[1] = 0;
		return (new);
	}
	i = -1;
	while (string[++i])
		new[i] = string[i];
	new[i++] = c;
	new[i] = 0;
	free(string);
	return (new);
}

static char	*ft_read(int fd, int *len)
{
	char	*buffer;
	char	*string;

	buffer = malloc(sizeof(char) * 2);
	if (!buffer)
		return (NULL);
	string = NULL;
	while (read(fd, buffer, 1) == 1)
	{
		string = ft_addchar(string, buffer[0], len);
		if (!string)
			return (free(buffer), NULL);
	}
	return (free(buffer), string);
}

char	*readstr(int fd)
{
	int			len;
	char		*string;

	len = 0;
	if (fd < 0)
		return (NULL);
	string = ft_read(fd, &len);
	if (!string)
		return (NULL);
	return (string);
}
