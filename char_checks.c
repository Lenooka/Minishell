/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   char_checks.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: johuber <johuber@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 19:23:22 by johuber           #+#    #+#             */
/*   Updated: 2025/06/01 13:11:44 by johuber          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

int	is_pipe(char *str)
{
	int	x;

	x = 0;
	while (str[x])
	{
		if (is_quote(str[x]))
			x = skip_quotes(str, x);
		if (!str[x])
			break ;
		if (str[x] == '|')
			return (1);
		x++;
	}
	return (0);
}

int	is_quote(char c)
{
	if (is_squote(c))
		return (1);
	if (is_dquote(c))
		return (1);
	return (0);
}

int	is_squote(char c)
{
	if (c == '\'')
		return (1);
	return (0);
}

int	is_dquote(char c)
{
	if (c == '\"')
		return (1);
	return (0);
}
