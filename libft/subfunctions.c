/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   subfunctions.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschor <bschor@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 09:06:24 by bschor            #+#    #+#             */
/*   Updated: 2023/11/23 10:47:41 by bschor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_printchar(char c, int **count)
{
	if (*count[0] != -1)
	{
		if (write(1, &c, 1) == -1)
			*count[0] = -1;
		else
			*count[0] = *count[0] + 1;
	}
}

void	ft_printstr(char *str, int **count)
{
	int	i;

	i = 0;
	if (!str)
	{
		ft_printstr("(null)", count);
		return ;
	}
	while (str[i])
	{
		ft_printchar(str[i], count);
		i++;
	}
}

void	ft_printnbr(int num, int **count, int un)
{
	char	*n;
	char	*base;

	base = "0123456789";
	if (un == 1)
		n = ft_itoa_unsigned((unsigned int)num, base);
	else
		n = ft_itoa_printf(num);
	if (!n)
	{
		*count[0] = -1;
		return ;
	}
	ft_printstr(n, count);
	free(n);
}

void	ft_printhex(long long unsigned int num, int **count, int maj)
{
	char	*base_min;
	char	*base_maj;
	char	*n;

	base_min = "0123456789abcdef";
	base_maj = "0123456789ABCDEF";
	if (maj == 1)
		n = ft_itoa_unsigned(num, base_maj);
	else
		n = ft_itoa_unsigned(num, base_min);
	if (!n)
	{
		*count[0] = -1;
		return ;
	}
	ft_printstr(n, count);
	free(n);
}
