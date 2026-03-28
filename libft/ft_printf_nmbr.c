/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_nmbr.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oltolmac <oltolmac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 15:20:33 by oltolmac          #+#    #+#             */
/*   Updated: 2024/10/29 14:14:15 by oltolmac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_putnbr(int n, int fd)
{
	int	len;

	len = 0;
	if (n == -2147483648)
	{
		len = write(fd, "-2147483648", 11);
		return (len);
	}
	if (n < 0)
	{
		len += write(fd, "-", 1);
		n = -n;
	}
	if (n > 9)
	{
		len += ft_putnbr(n / 10, fd);
		len += ft_putnbr(n % 10, fd);
	}
	else
	{
		n = n + '0';
		len += write(fd, &n, fd);
	}
	return (len);
}

int	ft_printf_nbr(int d)
{
	int	len;

	if (d == 0)
	{
		len = write(1, "0", 1);
		return (len);
	}
	len = ft_putnbr(d, 1);
	return (len);
}

static int	ft_hex(unsigned int n, int x)
{
	int	len;

	len = 0;
	if (n >= 16)
	{
		len += ft_hex(n / 16, x);
		len += ft_hex(n % 16, x);
	}
	else
	{
		if (n < 10)
		{
			len += ft_printf_char((n + '0'));
		}
		else
		{
			if (x == 0)
				len += ft_printf_char((n - 10 + 'a'));
			else if (x == 1)
				len += ft_printf_char((n - 10 + 'A'));
		}
	}
	return (len);
}

int	ft_printf_hex(unsigned int n, int x)
{
	int	len;

	if (n == 0)
	{
		len = write(1, "0", 1);
		return (len);
	}
	len = ft_hex(n, x);
	return (len);
}
