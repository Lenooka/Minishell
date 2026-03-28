/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils_seven.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oltolmac <oltolmac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 15:46:09 by oltolmac          #+#    #+#             */
/*   Updated: 2025/06/22 15:47:52 by oltolmac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

int	is_space(char c)
{
	if (c == ' ' || c == '\t' || c == '\r' \
		|| c == '\n' || c == '\f' || c == '\v')
		return (1);
	return (0);
}

int	has_space(char *str)
{
	int	x;

	x = 0;
	while (str[x])
	{
		if (is_space(str[x]))
			return (1);
		x++;
	}
	return (0);
}

int	calc_dollar(t_mini *mini, char *str, int x, int *count)
{
	if (is_valid_expansion(str[x + 1]))
		return (calc_exp_parsing(mini, str, x, count));
	(*count)++;
	x++;
	if (is_space(str[x]))
		return (x);
	if (str[x] == '?' || str[x] == '$')
		x++;
	else
	{
		while (is_valid_expansion(str[x]))
			x++;
	}
	if (str[x] == '$' || is_no_tokens(str[x]) || is_quote(str[x]))
		x = skip_token_merge(mini, str, x, count);
	return (x);
}

int	calc_quote(t_mini *mini, char *str, int x, int *count)
{
	if (is_dquote(str[x]))
	{
		x++;
		(*count)++;
		while (str[x] && !is_dquote(str[x]))
			x++;
		x++;
		if (str[x] == '$' || is_no_tokens(str[x]) || is_quote(str[x]))
			x = skip_token_merge(mini, str, x, count);
		return (x);
	}
	if (is_squote(str[x]))
	{
		x++;
		(*count)++;
		while (!is_squote(str[x]) && str[x])
			x++;
		x++;
		if (str[x] == '$' || is_no_tokens(str[x]) || is_quote(str[x]))
			x = skip_token_merge(mini, str, x, count);
		return (x);
	}
	return (x);
}
