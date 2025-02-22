/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschor <bschor@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 18:00:21 by bschor            #+#    #+#             */
/*   Updated: 2024/05/30 14:52:09 by bschor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"

char	*check_shlvl(char *shlvl)
{
	int	i;
	int	nbr;
	int	j;

	i = 0;
	while (shlvl[i] && shlvl[i] != '=')
		i++;
	j = i + 1;
	while (shlvl[j])
	{
		if (!ft_isdigit(shlvl[j]))
			return (ft_strdup("1"));
		j++;
	}
	nbr = ft_atoi(shlvl + i + 1);
	nbr += 1;
	return (ft_itoa(nbr));
}

void	ft_env(t_env **env, char **envp, t_system *systm)
{
	int		i;
	int		count;

	i = 0;
	count = 0;
	while (envp[i])
	{
		add_elem(env, envp[i], &count, systm);
		i++;
	}
}

void	ft_lstclear(t_env **lst)
{
	t_env	*tmp;

	while (*lst)
	{
		tmp = (*lst)->next;
		free((*lst)->key_value);
		free(*lst);
		*lst = tmp;
	}
}

void	ft_sort(t_env **current, t_env **sorted)
{
	t_env	*temp;

	if (!(*sorted) || ft_strncmp((*current)->key_value,
			(*sorted)->key_value, ft_strlen((*current)->key_value)) < 0)
	{
		(*current)->next = (*sorted);
		(*sorted) = (*current);
	}
	else
	{
		temp = (*sorted);
		while (temp->next && ft_strncmp(temp->next->key_value,
				(*current)->key_value, ft_strlen(temp->next->key_value)) < 0)
			temp = temp->next;
		(*current)->next = temp->next;
		temp->next = (*current);
	}
}

void	ft_lstsort(t_env **lst)
{
	t_env	*sorted;
	t_env	*current;
	t_env	*next;

	sorted = NULL;
	current = *lst;
	while (current)
	{
		next = current->next;
		ft_sort(&current, &sorted);
		current = next;
	}
	*lst = sorted;
}
