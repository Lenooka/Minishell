/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_calc_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oltolmac <oltolmac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 18:13:58 by johuber           #+#    #+#             */
/*   Updated: 2025/06/22 15:47:29 by oltolmac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

int	calc_merge_exp_pars(char *env, int *count)
{
	int	x;

	x = 0;
	if (is_space(env[x]))
		(*count)++;
	x = skip_spaces(env, x);
	while (env[x])
	{
		if (!is_space(env[x]))
		{
			(*count)++;
			while (!is_space(env[x]) && env[x])
				x++;
		}
		else
			x = skip_spaces(env, x);
	}
	if (is_space(env[x - 1]))
		return (1);
	return (0);
}

int	skip_token_merge_dol(t_mini *mini, char *s, int *x, int *count)
{
	int		exp_pars;
	int		exit;
	char	*env;

	exp_pars = 0;
	exit = 0;
	if (is_valid_expansion(s[(*x) + 1]))
	{
		env = get_env_value(mini, mini->env, get_env_name(mini, s, *x));
		if (has_space(env))
			exit = calc_merge_exp_pars(env, count);
		free(env);
	}
	(*x)++;
	if (s[(*x)] == '?')
		(*x)++;
	else
	{
		while (is_valid_expansion(s[(*x)]))
			(*x)++;
	}
	return (exit);
}

int	skip_token_merge(t_mini *mini, char *s, int x, int *count)
{
	if ((!is_quote(s[x]) && s[x] != '$' && !is_no_tokens(s[x])) || !s[x])
		return (x);
	if (is_quote(s[x]))
		x = calc_merge_quote(s, x);
	else if (s[x] == '$')
	{
		if (skip_token_merge_dol(mini, s, &x, count))
			return (x);
	}
	else if (is_no_tokens(s[x]))
	{
		while (is_no_tokens(s[x]) && s[x])
			x++;
	}
	if (is_quote(s[x]) || s[x] == '$' || is_no_tokens(s[x]))
		x = skip_token_merge(mini, s, x, count);
	return (x);
}

int	calc_char(t_mini *mini, char *str, int x, int *count)
{
	while (!is_space(str[x]) && !is_quote(str[x])
		&& str[x] && !is_arrow(str[x]) && str[x] != '$')
		x++;
	(*count)++;
	if (str[x] == '$' || is_no_tokens(str[x]) || is_quote(str[x]))
		x = skip_token_merge(mini, str, x, count);
	return (x);
}

int	calc_arrow(char *str, int x, int *count)
{
	while (is_arrow(str[x]))
		x++;
	(*count)++;
	return (x);
}
