/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oltolmac <oltolmac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 22:22:03 by olena             #+#    #+#             */
/*   Updated: 2024/09/09 19:12:54 by oltolmac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <stddef.h>

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char	*dp;
	unsigned char	*sp;

	if (!dest && !src)
		return (NULL);
	dp = (unsigned char *)dest;
	sp = (unsigned char *)src;
	while (n--)
		*dp++ = *sp++;
	return (dest);
}

/*int main() {
    char str[] = "Hello, world!";
    char buffer[20];

    ft_memcpy(buffer, str, 6);
    printf("ftmemcpy: %s\n", buffer);
    memcpy(buffer, str, 6);
    printf("memcpy: %s\n", buffer);   
    return 0;
}*/