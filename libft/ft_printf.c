/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschor <bschor@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 18:43:55 by bschor            #+#    #+#             */
/*   Updated: 2024/02/29 12:46:27 by bschor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdarg.h>

static void	ft_print_ptr(unsigned long long int n, int **count)
{
	char	*base;

	base = "0123456789abcdef";
	if (n >= 16)
	{
		ft_print_ptr(n / 16, count);
		ft_printchar(base[n % 16], count);
	}
	else
		ft_printchar(base[n % 16], count);
}

static void	ft_variable(char c, va_list args, int *count)
{
	if (c == 'c')
		ft_printchar((char)va_arg(args, int), &count);
	else if (c == 's')
		ft_printstr(va_arg(args, char *), &count);
	else if (c == 'p')
	{
		ft_printstr("0x", &count);
		ft_print_ptr(va_arg(args, unsigned long long int), &count);
	}
	else if (c == 'd' || c == 'i')
		ft_printnbr(va_arg(args, int), &count, 0);
	else if (c == 'u')
		ft_printnbr(va_arg(args, unsigned int), &count, 1);
	else if (c == 'x')
		ft_printhex(va_arg(args, int), &count, 0);
	else if (c == 'X')
		ft_printhex(va_arg(args, int), &count, 1);
	else if (c == '%')
		ft_printchar('%', &count);
	else
		*count = -1;
}

int	ft_printf(const char *format, ...)
{
	va_list	args;
	int		count;

	va_start(args, format);
	count = 0;
	while (format[0] && count != -1)
	{
		if (format[0] == '%' && count != -1)
		{
			ft_variable(format[1], args, &count);
			format++;
		}
		else if (format[0] != '%' && count != -1)
		{
			if (write(1, &format[0], 1) == -1)
				return (-1);
			count++;
		}
		format++;
	}
	va_end(args);
	return (count);
}
