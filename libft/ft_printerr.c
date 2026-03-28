/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printerr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oltolmac <oltolmac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 12:42:13 by olena             #+#    #+#             */
/*   Updated: 2025/01/19 15:58:14 by oltolmac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	int	ft_printerr_pars(va_list args, const char format)
{
	int	c;

	c = 0;
	if (format == 'c')
		c += ft_printerr_char(va_arg(args, int));
	else if (format == 's')
		c += ft_printerr_str(va_arg(args, char *));
	else if (format == 'p')
		c += ft_printerr_pointer(va_arg(args, unsigned long long));
	else if (format == 'd' || format == 'i')
		c += ft_printerr_nbr(va_arg(args, int));
	else if (format == 'u')
		c += ft_printerr_unsigned(va_arg(args, unsigned int));
	else if (format == 'x')
		c += ft_printerr_hex(va_arg(args, unsigned int), 0);
	else if (format == 'X')
		c += ft_printerr_hex(va_arg(args, unsigned int), 1);
	else if (format == '%')
		c += ft_printerr_percent();
	return (c);
}

int	ft_printerr(const char *str, ...)
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
			c += ft_printerr_pars(args, str[i + 1]);
			i++;
		}
		else
			c += ft_printerr_char(str[i]);
		i++;
	}
	va_end(args);
	return (c);
}
