/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   custom_split_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: johuber <johuber@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 19:31:56 by johuber           #+#    #+#             */
/*   Updated: 2025/05/11 17:21:23 by johuber          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

int	ft_slcheck_quotes(char *str, int len)
{
	int	x;
	int	count;

	x = 0;
	count = 0;
	while (x < len)
	{
		if (is_squote(str[x]))
			count++;
		x++;
	}
	return (count);
}

int	ft_dlcheck_quotes(char *str, int len)
{
	int	x;
	int	count;

	x = 0;
	count = 0;
	while (x < len)
	{
		if (is_dquote(str[x]))
			count++;
		x++;
	}
	return (count);
}

void	ft_split_continue(char **str, int *x)
{
	if (is_quote((*str)[(*x)]))
		*x = skip_quotes((*str), (*x));
	else
		(*x)++;
}

char	*c_ft_strndup(char *s, size_t n)
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
