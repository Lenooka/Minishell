/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   custom_split.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oltolmac <oltolmac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 19:28:40 by johuber           #+#    #+#             */
/*   Updated: 2025/06/19 20:04:04 by oltolmac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

static int	word_count(char *str, char c)
{
	int	count;
	int	x;

	x = skip_quotes(str, 0);
	count = 1;
	while (str[x] && str != NULL)
	{
		if (str[x] == c)
		{
			count++;
			x++;
		}
		if (is_quote(str[x]))
			x = skip_quotes(str, x);
		if (str[x])
			x++;
	}
	return (count);
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

static char	**ex_split(char **res, char **str, int *x, int *i)
{
	int	pos;

	(*x)++;
	pos = *x;
	if ((*i) == 0)
	{
		res[(*i)++] = c_ft_strndup(*str, (*x) - 1);
		if (!res[(*i) - 1])
			return (free_arr(res, *i));
	}
	while ((*str)[(*x)])
	{
		if (is_quote((*str)[(*x)]))
			(*x) = skip_quotes((*str), *x);
		else if ((*str)[(*x)] == '|' || !(*str)[(*x)])
			break ;
		else
			(*x)++;
	}
	res[(*i)++] = c_ft_strndup((*str) + pos, (*x) - pos);
	if (!res[(*i) - 1])
		return (free_arr(res, *i));
	return (res);
}

char	**ft_msplit(char *str, char c)
{
	char		**res;
	int			i;
	int			x;

	i = 0;
	if (str == NULL)
		return (NULL);
	res = (char **)malloc(sizeof(char *) * (word_count(str, c) + 1));
	if (!res)
		return (NULL);
	x = skip_quotes(str, 0);
	while (str[x] && str != NULL)
	{
		if (str[x] == c)
		{
			res = ex_split(res, &str, &x, &i);
			if (!res)
				return (NULL);
		}
		else
			ft_split_continue(&str, &x);
	}
	res[i] = NULL;
	return (res);
}
