#include "minishell.h"

int ft_strlen(char *str)
{
	int i;

	if (!str)
		return (0);
	i = 0;
	while (str[i])
		i++;
	return (i);
}

int if_blank(char c)
{
	if ((c <= 13 && c >= 9 )|| c == 32)
		return (1);
	return (0);
}


int	if_same_word(char *s1, char *s2)
{
	int	size1;
	int	size2;
	int	i;

	if (!s1 || !s2)
		return (0);
	size1 = ft_strlen(s1);
	size2 = ft_strlen(s2);
	if (size1 != size2)
		return (0);
	i = 0;
	while (s1[i])
	{
		if (s1[i] != s2[i])
			return (0);
		i++;
	}
	return (1);
}

char	*ft_substr(char *s, int start, int len)
{
	char	*str;
	int		i;

	if (!s)
		return (NULL);
	if (start > ft_strlen((char *)s))
		return (malloc(1));
	if (ft_strlen(s) - start < len)
		len = ft_strlen(s) - start;
	str = malloc(sizeof(char) * (len + 1));
	if (!str)
		return (NULL);
	i = 0;
	while (i < len && s[start])
	{
		str[i++] = s[start++];
	}
	str[i] = '\0';
	return (str);
}

char **ft_split_in_2(char *str)
{
	char **tab;
	char *s1;
	char *s2;
	int save;
	int i;

	tab = malloc(sizeof(char *) * 2);
	if (!tab || !str)
		return NULL;
	i = 0;
	while (str[i] && str[i] != '=')
		i++;

	s1 = ft_substr(str, 0, i);
	if (!s1)
		return NULL;
	i++;
	save = i;
	while(str[i] && !if_blank(str[i]))
		i++;
	s2 = ft_substr(str, save, i);
	if (!s2)
	{
		free(s1);
		return NULL;
	}
	tab[0] = s1;
	tab[1] = s2;
	return (tab);
}