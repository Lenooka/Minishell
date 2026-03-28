/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_s1trim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oltolmac <oltolmac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 11:27:04 by olena             #+#    #+#             */
/*   Updated: 2024/09/04 19:49:38 by oltolmac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	check_set(char c, const char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == c)
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*trim;
	int		e;
	int		s;
	int		i;

	s = 0;
	while (s1[s] && check_set(s1[s], set))
		s++;
	e = ft_strlen(s1);
	while (e > s && check_set(s1[e - 1], set))
		e--;
	trim = (char *)malloc(sizeof(char) * (e - s + 1));
	if (!trim)
		return (NULL);
	i = 0;
	while (i < e - s)
	{
		trim[i] = s1[s + i];
		i++;
	}
	trim[i] = '\0';
	return (trim);
}

/*int	main(int argc, char **argv)
{
	char *res;
	if (argc)
	{
		res = ft_strtrim(argv[1], argv[2]);
		printf("%s\n", res);
	}
	
	return (0);
}*/