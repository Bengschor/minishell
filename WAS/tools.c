#include "minishell.h"

void	ft_putstr_fd(char *s, int fd)
{
	if (!s)
		return ;
	write(fd, s, ft_strlen(s));
}

void	ft_bzero(void *s, size_t n)
{	
	if (!s)
		return ;
	if (n != 0)
		ft_memset(s, 0, n);
}

void	*ft_memset(void *b, int c, size_t len)
{
	char			*ptr;
	unsigned long	i;

	if (!b)
		return (NULL);
	i = 0;
	ptr = b;
	while (i < len)
	{
		ptr[i] = c;
		i++;
	}
	return (b);
}

char *join_and_free(char *s1, char *s2)
{
	char *temp;

	if (!s1)
		return (NULL);
	else if (!*s1)
		s1 = ft_strdup("");
	temp = ft_strjoin(s1, s2);
	free(s1);
	return (temp);
}

char	*ft_strdup(char *src)
{
	char	*dest;
	int		size;
	int		i;

	i = 0;
	if (!src)
		return (NULL);
	size = ft_strlen(src);
	dest = malloc(sizeof(char) * size + 1);
	if (!dest)
		return (0);
	while (src[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}