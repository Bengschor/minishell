/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschor <bschor@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 15:13:03 by bschor            #+#    #+#             */
/*   Updated: 2023/11/27 11:32:46 by bschor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static void	ft_bzero(void *s, int n)
{
	int	i;

	i = 0;
	while (i < n)
	{
		*((unsigned char *)(s + i)) = 0;
		i++;
	}
}

char	*ft_calloc_gnl(int count, int size)
{
	void	*ptr;

	ptr = malloc(count * size);
	if (!ptr)
		return (NULL);
	ft_bzero(ptr, count * size);
	return (ptr);
}

char	*ft_strjoin_free(char *s1, char *s2)
{
	char	*join;
	int		len;
	int		i;
	int		j;

	len = ft_strlen_gnl(s1) + ft_strlen_gnl(s2);
	i = -1;
	join = malloc(sizeof(char) * len + 1);
	if (!join || !s1 || !s2)
		return (ft_free_gnl(&s1), NULL);
	while (s1[++i] != 0)
		join[i] = s1[i];
	j = 0;
	while (s2[j] != 0)
		join[i++] = s2[j++];
	join[len] = 0;
	ft_free_gnl(&s1);
	return (join);
}

int	ft_strlen_gnl(const char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i] != 0)
		i++;
	return (i);
}

char	*ft_strchr_gnl(const char *s, int c)
{
	int	i;

	i = 0;
	if (c == 0)
		return ((char *)s + ft_strlen_gnl(s));
	while (s[i] != (char)c && s[i])
		i++;
	if (s[i] == (unsigned char)c)
		return ((char *)s + i);
	else
		return (NULL);
}
