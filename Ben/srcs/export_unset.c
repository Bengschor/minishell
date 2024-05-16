/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_unset.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschor <bschor@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 18:15:00 by bschor            #+#    #+#             */
/*   Updated: 2024/05/16 18:15:02 by bschor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"

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

int get_res(char *str)
{
	int i;

	i = 0;
	while(str[i] && str[i] != '=') //mot = // mot=
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
// int *get_lst(char **env)
// {
// 	int i;
// 	int *lst;
// 	int j;
// 	int min;

// 	i = 0;
// 	while (env[i])
// 		i++;
// 	lst = malloc(sizeof(int) * i);
// 	min = 0;
// 	i = 0;
// 	j = 0;
// 	while (env[i])
// 	{
// 		while ()
		 
// 		i++;
// 	}

// }

// int do_sort_env(int argc, char **env)
// {
// 	int i;
// 	int *lst;

// 	lst = get_lst(env);
// 	i = 0;
// 	while (env[lst[i]] != NULL)
// 	{
// 		printf("%s\n", env[lst[i]]);
// 		i++;
// 	}
// 	return (1);
// }

// export was=1 | ls
// export was=13 > echo coucou


int do_export(int argc, char **tabb, char ***env)
{
	//if export sans argument retourne env triée par ordre ascii
	int res;
	char **key;
	int i;

	i = 0;
	if (!tabb[1])
		return (do_env(argc, *env));
		// return (do_sort_env(argc, *env));
	while (tabb[i])
	{
		printf("tabb i :%s\n", tabb[i]);
		res = get_res(tabb[i]);
		printf("res :%d\n", res);
		if (res == 2)
			printf("zsh: bad assignement\n");
		else if (res == 3)
			printf("zsh: valeur not found\n");
		key = ft_split_in_2(tabb[i]);
		if (res == 1)
			ft_setenv(key[0], key[1], env);
		else if (res == 4)
			ft_setenv(key[0], 0, env);
		i++;
	}
	return (1);
}