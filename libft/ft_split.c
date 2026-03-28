/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: johuber <johuber@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 19:31:36 by olena             #+#    #+#             */
/*   Updated: 2025/03/18 19:29:37 by johuber          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>

static int	word_count(const char *s, char c)
{
	int	count;

	count = 0;
	while (*s && s != NULL)
	{
		if (*s == c)
			s++;
		else
		{
			count++;
			while (*s && *s != c)
				s++;
		}
	}
	return (count);
}

static char	*ft_strndup(const char *s, size_t n)
{
	char			*dest;
	unsigned int	i;

	i = 0;
	dest = (char *)malloc(sizeof(char) * (n + 1));
	if (!dest)
		return (NULL);
	while ((s[i] != '\0') && (i < n))
	{
		dest[i] = s[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

static char	**free_arr(char **str, int i)
{
	int	a;

	a = 0;
	while (a < i && str[a] != NULL)
	{
		free(str[a]);
		a++;
	}
	free(str);
	return (NULL);
}

static char	**ex_split(const char *s, char c, char **res)
{
	int			i;
	const char	*pos;

	i = 0;
	while (*s && s != NULL)
	{
		if (*s == c)
			s++;
		else
		{
			pos = s;
			while (*s && *s != c)
				s++;
			res[i++] = ft_strndup(pos, s - pos);
			if (!res[i - 1])
				return (free_arr(res, i));
		}
	}
	res[i] = NULL;
	return (res);
}

char	**ft_split(const char *s, char c)
{
	char		**res;

	if (s == NULL)
		return (NULL);
	res = (char **)malloc(sizeof(char *) * (word_count(s, c) + 1));
	if (!res)
		return (NULL);
	res = ex_split(s, c, res);
	return (res);
}

/*int    main(void)
{
    char	**res;
    int		i;

    i = 0;
    res = ft_split("Hello, world! How are you?", ' ');
    while (res[i])
    {
        printf("%s\n", res[i]);
        i++;
    }
    return (0);
}*/