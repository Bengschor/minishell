/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschor <bschor@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 11:26:18 by bschor            #+#    #+#             */
/*   Updated: 2023/10/19 12:04:29 by bschor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*sub;
	size_t	i;

	i = 0;
	if (start < 0 || !s)
		return (NULL);
	if (len >= ft_strlen(s) - start + 1)
		len = ft_strlen(s) - start;
	if (start > ft_strlen(s))
		len = 0;
	sub = malloc(sizeof(char) * len + 1);
	if (!sub)
		return (NULL);
	if (start < ft_strlen(s) && len > 0)
	{
		while (s[start + i] && i < len)
		{
			sub[i] = s[start + i];
			i++;
		}
	}
	sub[i] = 0;
	return (sub);
}
