/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschor <bschor@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 14:40:07 by bschor            #+#    #+#             */
/*   Updated: 2023/10/23 08:47:21 by bschor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t	i;

	i = 0;
	if (n == 0)
		return (NULL);
	while (*(unsigned char *)(s + i) != (unsigned char)c && i < n - 1)
		i++;
	if (*(unsigned char *)(s + i) == (unsigned char)c)
		return ((void *)s + i);
	else
		return (NULL);
}
