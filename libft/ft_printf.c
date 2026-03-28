/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oltolmac <oltolmac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 12:42:13 by olena             #+#    #+#             */
/*   Updated: 2024/10/29 14:19:26 by oltolmac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	int	ft_printf_pars(va_list args, const char format)
{
	int	c;

	c = 0;
	if (format == 'c')
		c += ft_printf_char(va_arg(args, int));
	else if (format == 's')
		c += ft_printf_str(va_arg(args, char *));
	else if (format == 'p')
		c += ft_printf_pointer(va_arg(args, unsigned long long));
	else if (format == 'd' || format == 'i')
		c += ft_printf_nbr(va_arg(args, int));
	else if (format == 'u')
		c += ft_printf_unsigned(va_arg(args, unsigned int));
	else if (format == 'x')
		c += ft_printf_hex(va_arg(args, unsigned int), 0);
	else if (format == 'X')
		c += ft_printf_hex(va_arg(args, unsigned int), 1);
	else if (format == '%')
		c += ft_printf_percent();
	return (c);
}

int	ft_printf(const char *str, ...)
{
	int		i;
	va_list	args;
	int		c;

	i = 0;
	c = 0;
	va_start(args, str);
	while (str[i])
	{
		if (str[i] == '%')
		{
			c += ft_printf_pars(args, str[i + 1]);
			i++;
		}
		else
			c += ft_printf_char(str[i]);
		i++;
	}
	va_end(args);
	return (c);
}
