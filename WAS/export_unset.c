#include "minishell.h"

int get_pos(char *env, char c)
{
	int i;

	i = 0;
	while (env[i])
	{
		if (env[i] == c)
			return (i);
		i++;
	}
	return (-1);
}
int if_in_env(char *var, char **env)
{
	char *str;
	int pos;

	while (*env != NULL)
	{
		pos = get_pos(*env, '=');
		if (pos == -1)
		{
			printf("error env\n");
			exit(1);
		}
		str = ft_substr(*env, 0, pos);
		if (if_same_word(str, var))
		{
			free(str);
			return (1);
		}
		env++;
	}
	return (0);
}

int do_unset(char **tab, int argc, char **env)
{
	int i;

	if (argc > 1)
	{
		i = 1;
		while (i < argc)
		{
			if (if_in_env(tab[i], env))
				unsetenv(tab[i]);
			i++;
		}
	}
	else
		printf("unset: not enough arguments\n");
	return (1);
}

int get_res(char *str)
{
	int i;

	i = 0;
	while (str[i] && !if_blank(str[i]))
		i++;
	if (str[i] == '\0')
		return (1);
	else if (if_blank(str[i]) && str[i + 1] == '=' && if_blank(str[i + 2]))
		return (2);
	else if (if_blank(str[i] && str[i + 1] == '=' && !if_blank(str[i + 2])))
		return (3);
	else if (if_blank(str[i]) && str[i - 1] == '=')
		return (4);
	return (1);
}



int do_export(int argc, char **tab, char ***env)
{
	//if export sans argument retourne env triée par ordre ascii
	int res;
	char **key;
	int size;

	size = 0;
	if (!tab[1])
	{
		do_env(argc, *env);
		return (0);
	}
	while ((*env)[size] != NULL)
		size++;
	res = get_res(tab[1]);
	if (res == 2)
	{
		printf("zsh: bad assignement\n");
		return (0);
	}
	else if (res == 3)
	{
		printf("zsh: valeur not found\n");
		return (0);
	}
	key = ft_split_in_2(tab[1]);
	if (res == 1)
		ft_setenv(key[0], key[1], env, size);
	else if (res == 4)
		ft_setenv(key[0], 0, env, size);
	return (1);
}