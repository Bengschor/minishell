/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                   		:+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschor <bschor@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 18:15:15 by bschor            #+#    #+#             */
/*   Updated: 2024/05/28 13:31:53 by bschor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"

int	ch_oldpwd(t_env **env, t_system *systm)
{
	char	*pwd;
	char	temp[1024];
	t_env	*old_pwd;
	t_env	*ppwd;

	old_pwd = ft_super_getenv("OLDPWD", env);
	if (old_pwd == NULL)
	{
		if (ft_add_new(env, "OLDPWD= ") == 0)
			return (0);
		old_pwd = ft_super_getenv("OLDPWD", env);
	}
	pwd = ft_getenv("PWD", env);
	old_pwd->key_value = ft_realloc(old_pwd->key_value, pwd, systm);
	if (old_pwd->key_value == NULL)
		return (0);
	if (getcwd(temp, sizeof(temp)) == NULL)
		return (0);
	ppwd = ft_super_getenv("PWD", env);
	ppwd->key_value = ft_realloc(ppwd->key_value, temp, systm);
	if (ppwd->key_value == NULL)
		return (0);
	return (1);
}

int	keyword_path(t_system *systm, char *str, char *key)
{
	t_env	*old_pwd;
	t_env	*pwd;

	if (!str)
		return (ft_printf_err("minishell: cd: %s not set\n", key), 1);
	if (chdir(str) != 0)
		return (ft_printf_err("minishell: cd: %s: No such file or directory\n",
				str), 1);
	old_pwd = ft_super_getenv("OLDPWD", systm->env);
	if (old_pwd == NULL)
	{
		if (ft_add_new(systm->env, "OLDPWD=") == 0)
			return (0);
		old_pwd = ft_super_getenv("OLDPWD", systm->env);
	}
	old_pwd->key_value = ft_realloc(old_pwd->key_value,
			ft_getenv("PWD", systm->env), systm);
	if (old_pwd->key_value == NULL)
		return (0);
	pwd = ft_super_getenv("PWD", systm->env);
	pwd->key_value = ft_realloc(pwd->key_value, str, systm);
	if (pwd->key_value == NULL)
		return (0);
	return (1);
}

int	get_last_c(char *str, char c)
{
	int	i;
	int	save;

	i = 0;
	save = -1;
	while (str[i])
	{
		if (str[i] == c)
			save = i;
		i++;
	}
	return (save);
}

int	get_ex_code(char *str)
{
	if (str[0] == '-')
		return (256 + ft_atoi(str));
	else
		return (ft_atoi(str));
}
