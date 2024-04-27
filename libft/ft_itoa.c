/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschor <bschor@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 23:53:45 by bschor            #+#    #+#             */
/*   Updated: 2023/10/18 23:54:11 by bschor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_intlen(int n)
{
	int	i;

	i = 0;
	if (n == 0)
		return (1);
	if (n < 0)
		i++;
	while (n != 0)
	{
		n = n / 10;
		i++;
	}
	return (i);
}

char	*ft_itoa(int n)
{
	char			*str;
	int				len;
	long int		num;

	len = ft_intlen(n);
	str = malloc(sizeof(char) * (len + 1));
	if (!str)
		return (NULL);
	str[len] = 0;
	num = n;
	if (n < 0)
	{
		str[0] = '-';
		num = -num;
	}
	if (num == 0)
		str[0] = 48;
	while (num != 0 && len > 0)
	{
		str[len - 1] = (num % 10) + 48;
		num = num / 10;
		len--;
	}
	return (str);
}
