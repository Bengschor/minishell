/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschor <bschor@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 16:18:11 by bschor            #+#    #+#             */
/*   Updated: 2023/10/23 08:46:18 by bschor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (!needle[j])
		return ((char *)haystack);
	while (haystack[i] && i < len)
	{
		while (needle[j] == haystack[i + j] && haystack[i + j] != 0
			&& i + j < len)
			j++;
		if (!needle[j])
			return ((char *)haystack + i);
		j = 0;
		i++;
	}
	return (NULL);
}
