/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printerr_chars.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oltolmac <oltolmac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/19 15:52:52 by oltolmac          #+#    #+#             */
/*   Updated: 2025/01/19 15:58:20 by oltolmac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_printerr_char(int c)
{
	write(2, &c, 1);
	return (1);
}

int	ft_printerr_str(char *s)
{
	int	len;
	int	c;

	if (s == NULL)
	{
		write(2, "(null)", 6);
		return (6);
	}
	c = ft_strlen(s);
	len = write(2, s, c);
	return (len);
}

int	ft_printerr_percent(void)
{
	int		len;
	char	c;

	c = '%';
	len = ft_printerr_char(c);
	return (len);
}
