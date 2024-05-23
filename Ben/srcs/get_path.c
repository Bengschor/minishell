/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschor <bschor@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 18:00:21 by bschor            #+#    #+#             */
/*   Updated: 2024/05/22 10:29:29 by bschor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"

char *join_and_free(char *s1, char *s2, t_system *systm)
{
    char *temp;

    if (!s1)
    {
   		s1 = malloc(1);
		if (!s1)
			return (ft_crash(systm), NULL);
   		s1[0] = '\0';
    }
    temp = ft_strjoin(s1, s2);
	if (!temp)
			return (ft_crash(systm), NULL);
    free(s1);
    return (temp);
}

char *ft_strtok(char *str, char c, int nbr, t_system *systm)
{
    int start;
    int i;
    char *token;

    i = 0;
    start = 0;
    while (str[i])
    {
   		if (str[i] == c && nbr == 0)
   			break ;
   		else if (str[i] == c && nbr != 0)
   		{
   			start = i + 1;
   			nbr--;
   		}
   		i++;
    }
    if (str[i] == '\0' && nbr != 0)
   		return (NULL);
    token = ft_substr(str, start, i - start);
    if (!token)
   		return (ft_crash(systm), NULL);
    return (token);
}

char *get_path(char *cmd, t_system *systm)
{
    char *path;
    char *path_token;
    char *full_path;
    int i;

    i = 1;
    if (is_builtins(cmd))
        return (ft_strdup(cmd));
    path = getenv("PATH");
    path_token = ft_strtok(path, ':', i, systm);
	full_path = NULL;
	systm->status = 126;
    while (path_token != NULL)
    {
    	full_path = join_and_free(path_token, "/", systm);
    	full_path = join_and_free(full_path, cmd, systm);
		if (!access(full_path, F_OK | X_OK))
			return (full_path);
		else if (access(full_path, F_OK) && !access(full_path, X_OK))
			return (ft_printf_err(XOKACC, full_path), NULL);
    	i++;
    	path_token = ft_strtok(path, ':', i, systm);
    }
	systm->status = 127;
    free(full_path);
    return (ft_printf_err("minishell: %s: command not found\n", cmd), NULL);
}

