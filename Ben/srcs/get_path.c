/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschor <bschor@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 18:00:21 by bschor            #+#    #+#             */
/*   Updated: 2024/05/15 18:22:13 by bschor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"

char *join_and_free(char *s1, char *s2)
{
    char *temp;

    if (!s1)
    {
   		s1 = malloc(1);
   		s1[0] = '\0';
    }
    temp = ft_strjoin(s1, s2);
    free(s1);
    return (temp);
}

char *ft_strtok(char *str, char c, int nbr)
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
   		return (NULL);
    return (token);
}

char *check_path(char *cmd)
{
    char *path;
    char *path_token;
    char *full_path;
    int i;

    i = 1;
    path = getenv("PATH");
    path_token = ft_strtok(path, ':', i);
    while (path_token != NULL)
    {
    	full_path = join_and_free(path_token, "/");
    	full_path = join_and_free(full_path, cmd);
    	if (access(full_path, F_OK))
			return (printf("minishell: %s: command not found\n", cmd), NULL);
		if (access(full_path, X_OK))
			return (full_path);
		else
			return (printf(XOKACC, full_path), NULL);
    	i++;
    	path_token = ft_strtok(path, ':', i);
    }
    free(full_path);
    return (NULL);
}

