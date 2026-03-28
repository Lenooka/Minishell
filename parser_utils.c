/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oltolmac <oltolmac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 19:55:04 by johuber           #+#    #+#             */
/*   Updated: 2025/06/22 15:46:52 by oltolmac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

int	rev_skip_spaces(char *str, int x)
{
	while (x > 0)
	{
		if (is_space(str[x]))
			x--;
		else
			break ;
	}
	return (x);
}

int	skip_spaces(char *str, int x)
{
	while (str[x])
	{
		if (is_space(str[x]))
			x++;
		else
			break ;
	}
	return (x);
}

int	skip_quotes(char *str, int x)
{
	if (is_dquote(str[x]))
	{
		x++;
		while (!is_dquote(str[x]) && str[x])
			x++;
		if (str[x])
			x++;
	}
	if (is_squote(str[x]))
	{
		x++;
		while (!is_squote(str[x]) && str[x])
			x++;
		if (str[x])
			x++;
	}
	if (is_dquote(str[x]) || is_squote(str[x]))
		skip_quotes(str, x);
	return (x);
}

void	make_empty_arr(int count, t_cmd *cmd)
{
	int	*res;
	int	x;

	x = 0;
	cmd = get_last_node(cmd);
	res = (int *)malloc(sizeof(int) * (count));
	if (!res)
		return ;
	while (x < count)
	{
		res[x] = 0;
		x++;
	}
	cmd->empty = res;
}

char	**calc_tokens(t_mini *mini, char *str, t_cmd *cmd)
{
	int		x;
	int		count;
	char	**res;

	count = 0;
	x = skip_spaces(str, 0);
	while (str[x])
	{
		if (is_quote(str[x]))
			x = calc_quote(mini, str, x, &count);
		else if (str[x] == '$')
			x = calc_dollar(mini, str, x, &count);
		else if (is_arrow(str[x]))
			x = calc_arrow(str, x, &count);
		else if (!is_space(str[x]))
			x = calc_char(mini, str, x, &count);
		if (is_space(str[x]))
			x = skip_spaces(str, x);
	}
	res = (char **)malloc(sizeof(char *) * (count + 1));
	if (cmd)
		make_empty_arr(count, cmd);
	if (res)
		res[0] = NULL;
	return (res);
}
