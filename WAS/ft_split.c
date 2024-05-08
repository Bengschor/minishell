#include "minishell.h"

size_t	ft_strlcpy(char *dest, char *src, size_t size)
{
	unsigned int	i;
	unsigned int	l;

	if (!dest || !src)
		return (0);
	l = ft_strlen(src);
	i = 0;
	if (size != 0)
	{
		while (src[i] && i < size - 1)
		{
			dest[i] = src[i];
			i++;
		}
		dest[i] = '\0';
	}
	return (l);
}

int	free_tab(char **tab, int i)
{
	while (i >= 0)
	{
		free(tab[i]);
		i--;
	}
	free(tab);
	return (0);
}

unsigned long	count_words(char *s, char c)
{	
	int	i;
	int	count;

	count = 0;
	if (s[0] != c)
		count++;
	if (s[ft_strlen(s) - 1] == c)
		count--;
	i = 0;
	while (s[i])
	{
		if (s[i] == c && (s[i + 1] != c))
			count++;
		i++;
	}
	return (count);
}

int	add_str(char **str, char *s, char c)
{
	int		i;
	int		j;
	int		k;
	char	*ptr;

	i = -1;
	j = -1;
	ptr = (char *)s;
	while (s[++i])
	{
		if (s[i] != c)
		{
			k = 0;
			while (s[i + k] && s[i + k] != c)
				k++;
			str[++j] = malloc(sizeof(char) * (k + 1));
			if (!str[j])
				return (free_tab(str, j - 1));
			ft_strlcpy(str[j], ptr + i, k + 1);
			i += k - 1;
		}
	}
	return (1);
}

char	**ft_split(char const *s, char c, int *ac)
{
	int		words;
	char	**tab;

	if (!s)
		return (0);
	if (s[0] == '\0')
		words = 0;
	else
		words = count_words((char *)s, c);
	*ac = words;
	tab = malloc(sizeof(char *) * (words + 1));
	if (!tab)
		return (NULL);
	if (words > 0)
	{
		if (!add_str(tab, (char *)s, c))
			return (NULL);
	}
	tab[words] = 0;
	return (tab);
}