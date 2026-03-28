/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olena <olena@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 13:52:22 by oltolmac          #+#    #+#             */
/*   Updated: 2024/09/05 00:48:34 by olena            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned int	i;
	unsigned int	j;

	i = 0;
	j = 0;
	if (n == 0)
		return (0);
	while ((i < n - 1) && (j < n - 1) && s1[i] == s2[j])
	{
		if (s1[i] == '\0' || s2[j] == '\0')
			break ;
		i++;
		j++;
	}
	return ((unsigned char)s1[i] - (unsigned char)s2[j]);
}

/*int	main(int argc, char **argv)
{
	int	r;

	if (argc)
	{
		r = ft_strncmp(argv[1], argv[2], 2);
		printf("%d\n", r);
		r = strncmp(argv[1], argv[2], 2);
		printf("%d\n", r);
	}
}
*/