/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_printf.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschor <bschor@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 12:11:06 by bschor            #+#    #+#             */
/*   Updated: 2023/11/23 11:01:02 by bschor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_intlen_unsigned(unsigned int n, int base)
{
	unsigned int	i;

	i = 0;
	if (n == 0)
		return (1);
	if (n < 0)
		i++;
	while (n != 0)
	{
		n = n / base;
		i++;
	}
	return (i);
}

char	*ft_itoa_unsigned(unsigned int n, char *base)
{
	char			*str;
	int				len;
	long int		num;

	len = ft_intlen_unsigned(n, ft_strlen(base));
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
		str[len - 1] = base[(num % ft_strlen(base))];
		num = num / ft_strlen(base);
		len--;
	}
	return (str);
}

static int	ft_intlen(int n, int base)
{
	int	i;

	i = 0;
	if (n == 0)
		return (1);
	if (n < 0)
		i++;
	while (n != 0)
	{
		n = n / base;
		i++;
	}
	return (i);
}

char	*ft_itoa_printf(int n)
{
	char			*str;
	int				len;
	long int		num;

	len = ft_intlen(n, 10);
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
		str[len - 1] = (num % 10 + 48);
		num = num / 10;
		len--;
	}
	return (str);
}
