/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oltolmac <oltolmac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 19:23:19 by oltolmac          #+#    #+#             */
/*   Updated: 2025/05/30 14:06:46 by oltolmac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	olen;
	size_t	tlen;
	char	*join;

	olen = ft_strlen(s1);
	tlen = ft_strlen(s2);
	join = (char *)malloc(sizeof(char) * (olen + tlen + 1));
	if (!join)
		return (NULL);
	ft_strlcpy(join, s1, olen + 1);
	ft_strlcpy(join + olen, s2, tlen + 1);
	return (join);
}

/*int	main(int argc, char **argv)
{
	if (argc)
		printf("%s", ft_strjoin(argv[1], argv[2]));
	return (0);
}*/