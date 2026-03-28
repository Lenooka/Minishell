/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olena <olena@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 13:58:58 by oltolmac          #+#    #+#             */
/*   Updated: 2024/09/04 23:21:10 by olena            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_strcpy(char *dest, const char *s)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (s[i] != '\0')
	{
		dest[j] = s[i];
		i++;
		j++;
	}
	dest[j] = '\0';
	return (dest);
}

char	*ft_strdup(const char *s)
{
	char	*dest;
	int		len;

	len = ft_strlen(s);
	dest = (char *)malloc(sizeof(char) * len + 1);
	if (!dest)
		return (NULL);
	ft_strcpy(dest, s);
	return (dest);
}

/*int	main(int argc, char **argv)
{
	char *d;
	if (argc && argv[1])
	{
		d = ft_strdup(argv[1]);
		printf("my strdup = %s\n", d);
		d = strdup(argv[1]);
		printf("standart strdup = %s\n", d);
	}
	return (0);
}*/