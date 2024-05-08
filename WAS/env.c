#include "minishell.h"

char *get_input()
{
    char *str;
    char *s;
    char cwd[1024];

    if (getcwd(cwd, sizeof(cwd)) == NULL)
        return (NULL);
    s = ft_strjoin("minishell prompt ", ft_strrchr(cwd, '/'));
    s = ft_strjoin(s, " $> ");
    str = readline(s);
    if (!*str)
        return (str);
    add_history(str);
    return (str);
}

int if_key(char *str, char **env)
{
    char *key;
    int i;
    int j;

    i = 0;
    while (env[i] != NULL)
    {
        j = 0;
        while (env[i][j] && env[i][j] != '=')
            j++;
        key = malloc(j * sizeof(char));
        key[j] = '\0';
        while (--j >= 0)
            key[j] = env[i][j];
        if (if_same_word(key, str))
            return (1);
        i++;
    }
    return (0);
}

int ft_setenv(char *key, char *value, char ***env, int size)
{
	char **tab;
	int i;
	int x;

	x = 0;
	tab = (char **)malloc((size + 2) * sizeof(char *));
	if (!tab)
		return (0);
	i = 0;
	while (i < size)
	{
		if (if_key(key, *env))
		{
			printf("issame i : %d\n", i);
			tab[i] = ft_strjoin(key, "=");
			tab[i] = ft_strjoin(tab[i], value);
			x = 1;
		}
		else
			tab[i] = (*env)[i];
		i++;
	}
	if (x == 0)
	{
		tab[i] = ft_strjoin(key, "=");
		tab[i] = ft_strjoin(tab[i], value);
		tab[i + 1] = NULL;
	}
	*env = tab;
	return (1);
}

char *get_key_value(char *var, char **value)
{
    char *key;
    int i;
    int j;

    i = 0;
    while (var[i] && var[i] != '=')
        i++;
    key = malloc(i * sizeof(char));
    j = 0;
    while (j < i)
    {
        key[j] = var[j];
        j++;
    }
    key[j] = '\0';
    i++;
    j = i;
    while (var[i])
        i++;
    (*value) = var + j;
    return (key);
}

char *ft_getenv(char *str, char **env)
{
    int i;
    char *key;
    char *value;

    i = 0;
    while (env[i] != NULL)
    {
        key = get_key_value(env[i], &value);
        if (if_same_word(key, str))
            return (value);
        i++;
    }
    return (NULL);
}
