/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschor <bschor@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 11:34:59 by bschor            #+#    #+#             */
/*   Updated: 2024/04/25 11:57:14 by bschor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	int	i;

	i = 0;
	if (!s)
		return (NULL);
	if (c == 0)
		return ((char *)s + ft_strlen(s));
	while (s[i] != (char)c && s[i])
		i++;
	if (s[i] == (unsigned char)c)
		return ((char *)s + i);
	else
		return (NULL);
}
