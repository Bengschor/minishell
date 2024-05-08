#include "minishell.h"

int is_blank(char *str)
{
	int i;
	int count;

	count = 0;
	i = 0;
	while (str[i])
	{
		if (if_blank(str[i]))
			count++;
		i++;
	}
	if (count == i)
		return (1);
	return (0);
}

char *ft_strjoin(char *s1, char *s2)
{
	int i;
	int j;
	char *str;

	if (!s1 || !s2)
		return (NULL);
	str = malloc(sizeof(char) * ft_strlen(s1) + ft_strlen(s2) + 1);
	i = 0;
	while (s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j])
		str[i++] = s2[j++];
	str[i] = '\0';
	return (str);
}

char *ft_strrchr(char *str, char c)
{
    int i;
    int save;

    i = 0;
    save = 0;
    while (str[i])
    {
        if (str[i] == c)
            save = i;
        i++;
    }
    if (save == 0)
        return NULL;
    return (str + save + 1);
}