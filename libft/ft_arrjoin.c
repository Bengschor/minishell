/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arrjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschor <bschor@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 17:38:46 by bschor            #+#    #+#             */
/*   Updated: 2024/07/24 18:52:47 by bschor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	free_strs(char **strs, int i)
{
	while (i > 0)
	{
		free(strs[i]);
		i--;
	}
	free(strs);
}

static int	ft_apparr(char **dest, char **srcs, int max)
{
	int	i;

	i = 0;
	while (dest[i] && i < max)
		i++;
	while (i < max)
	{
		dest[i] = ft_strdup(srcs[i]);
		if (!dest[i])
			return (free_strs(dest, i), 1);
		i++;
	}
	dest[i] = NULL;
	return (0);
}

char	**ft_arrjoin(char **a1, char **a2)
{
	int		len1;
	int		len2;
	char	**join;

	len1 = ft_strslen(a1);
	len2 = ft_strslen(a2);
	join = malloc(sizeof(char *) * (len1 + len2 + 1));
	if (!join)
		return (NULL);
	join[0] = NULL;
	if (!ft_apparr(join, a1, len1) || !ft_apparr(join, a2, len1 + len2))
		return (NULL);
	return (join);
}
