/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oltolmac <oltolmac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 14:35:15 by oltolmac          #+#    #+#             */
/*   Updated: 2024/09/09 19:10:43 by oltolmac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		if (*(unsigned char *)(s + i) == (unsigned char) c)
			return ((void *)(s + i));
		i++;
	}
	return (NULL);
}

/*int main() 
{
    char str[] = "Hello, world!";
    const char *ps;

    ps = ft_memchr(str, 'l', 5);
    printf("ftmemchr: %s\n", ps);
    ps = memchr(str, 'l', 5);
    printf("memchr: %s\n", ps);   
    return 0;
}*/