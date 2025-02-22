/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschor <bschor@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 18:15:11 by bschor            #+#    #+#             */
/*   Updated: 2024/07/24 18:59:07 by bschor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"

int	do_echo(int argc, char **argv)
{
	int	i;
	int	nw_line;

	nw_line = 1;
	i = 1;
	if (if_option(argv[i]))
	{
		nw_line = 0;
		i++;
	}
	while (i < argc)
	{
		printf("%s", argv[i]);
		if (i < argc - 1)
			printf(" ");
		i++;
	}
	if (nw_line)
		printf("\n");
	return (0);
}

int	do_cd(char *path, t_system *systm)
{
	char	*str;
	int		res;

	if (!path || path[0] == 126)
	{
		str = ft_strdup(ft_getenv("HOME", systm->env));
		res = keyword_path(systm, str, "HOME");
		return (free(str), res);
	}
	else if (if_same_word((char *)path, "-"))
	{
		str = ft_strdup(ft_getenv("OLDPWD", systm->env));
		res = keyword_path(systm, str, "OLDPWD");
		printf("%s\n", str);
		return (free(str), res);
	}
	else if (chdir(path) != 0)
	{
		ft_printf_err("minishell: cd: %s: No such file or directory\n", path);
		return (1);
	}
	else
		ch_oldpwd(systm->env, systm);
	return (0);
}

int	do_pwd(t_system *systm)
{
	char	cwd[1024];
	char	*str;

	str = ft_getenv("PWD", systm->env);
	if (getcwd(cwd, sizeof(cwd)) != NULL)
		printf("%s\n", cwd);
	else if (str != NULL)
		printf("%s\n", str);
	else
		perror("getcwd");
	return (0);
}

int	do_env(int argc, char **argv, t_env **env)
{
	t_env	*curr;

	if (argc > 1)
	{
		ft_printf_err("env: %s: No such file or directory\n", argv[1]);
		return (0);
	}
	curr = *env;
	while (curr != NULL)
	{
		printf("%s\n", curr->key_value);
		curr = curr->next;
	}
	return (1);
}

int	do_exit(int ac, char **av, t_system *systm)
{
	int	ex_code;

	ex_code = 1;
	printf("exit\n");
	if (ac > 2)
		return (ft_printf_err("minishell: exit: too many arguments\n"), 1);
	else if (ac == 1)
		ex_code = 0;
	else if (is_all_digit(av[1]))
		ex_code = get_ex_code(av[1]);
	else
	{
		ft_printf_err("minishell: exit: %s: numeric argument required\n",
			av[1]);
		ex_code = 255;
	}
	ft_free_systm(systm);
	free_env(systm);
	close(systm->std[1]);
	close(systm->std[0]);
	exit(ex_code);
}
