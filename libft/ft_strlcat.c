/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschor <bschor@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/15 14:43:58 by bschor            #+#    #+#             */
/*   Updated: 2024/04/19 13:23:50 by bschor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	j;
	size_t	i;
	size_t	lsrc;

	if (!dst || !src)
		return (0);
	lsrc = ft_strlen(src);
	i = 0;
	j = 0;
	while (dst[j] && j < dstsize)
		j++;
	while (src[i] && (j + i + 1) < dstsize)
	{
		dst[j + i] = src[i];
		i++;
	}
	if (j != dstsize)
		dst[j + i] = 0;
	return (j + lsrc);
}
