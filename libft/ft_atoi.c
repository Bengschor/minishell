/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschor <bschor@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 14:29:35 by bschor            #+#    #+#             */
/*   Updated: 2023/10/23 08:37:49 by bschor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_atoi(const char *str)
{
	int		i;
	int		neg;
	long	res[2];

	i = 0;
	neg = 1;
	res[0] = 0;
	res[1] = 0;
	while (((str[i] >= 9 && str[i] <= 13) || str[i] == 32) && str[i])
		i++;
	if ((str[i] == '+' || str[i] == '-') && str[i])
	{
		if (str[i++] == '-')
			neg = -1;
	}
	while ((str[i] >= 48 && str[i] <= 57) && str[i])
	{
		res[0] = res[0] * 10 + (str[i++] - 48);
		if (res[1] > res[0] && neg > 0)
			return (-1);
		else if (res[1] > res[0] && neg < 0)
			return (0);
		res[1] = res[0];
	}
	return (neg * res[0]);
}
