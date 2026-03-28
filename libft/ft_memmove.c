/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oltolmac <oltolmac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 22:24:12 by olena             #+#    #+#             */
/*   Updated: 2024/09/09 19:38:55 by oltolmac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char	*dp;
	unsigned char	*sp;

	if (!dest && !src)
		return (NULL);
	dp = (unsigned char *)dest;
	sp = (unsigned char *)src;
	if (dp < sp)
		while (n--)
			*dp++ = *sp++;
	else
	{
		dp += n;
		sp += n;
		while (n--)
			*--dp = *--sp;
	}
	return (dest);
}

/*void    *ft_memmove(void *dest, const void *src, size_t n)
{
	int			i;

    if (!dest && !src)
        return (dest);
	i = 0;
    if (dest < src)
	{
        while ((size_t)i < n)
		{
			((unsigned char *)dest)[i] = ((unsigned char *)src)[i];
			i++;
		}
	}
	else
    {
		i = n - 1;
		while (i >= 0)
		{
			((unsigned char *)dest)[i] = ((unsigned char *)src)[i];
			i--;
		}
    }
    return (dest);
}*/

/*int main() {
    char str[] = "Hello, world!";
    char buffer[20];

    ft_memmove(buffer, str + 7, 6);
    printf("ftmemmove: %s\n", buffer);
    memmove(buffer, str + 7, 6);
    printf("memmove: %s\n", buffer);

    return 0;
}*/