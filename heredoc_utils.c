/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oltolmac <oltolmac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 17:54:07 by johuber           #+#    #+#             */
/*   Updated: 2025/06/19 20:25:22 by oltolmac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

void	heredoc_warn(t_mini *mini, char *del, char *line)
{
	printf("Warning: here-document delimited ");
	printf("by end-of-file (wanted '");
	printf("%s')\n", del);
	free(del);
	free_exit_heredoc(mini, line, NULL);
}

int	is_valid_expansionh(char c)
{
	if (is_quote(c) || c == '=' || c == '|' || c == '$' || c == '\0'
		|| is_arrow(c))
		return (0);
	return (1);
}

int	h_skip_expansion(char *str, int x)
{
	x++;
	if (str[x] == '$')
	{
		x++;
		return (x);
	}
	while (!is_space(str[x]) && !is_quote(str[x])
		&& str[x] && !is_arrow(str[x]) && str[x] != '$')
	{
		if (str[x] == '?')
		{
			x++;
			break ;
		}
		x++;
	}
	return (x);
}

char	*here_expander(t_mini *mini, char *str, char *res, int *x)
{
	char	*tmp;

	mini->free = res;
	tmp = get_env_value(mini, mini->env, get_env_name(mini, str, *x));
	mini->free = NULL;
	res = p_ft_strjoin(mini, res, tmp);
	*x = h_skip_expansion(str, *x);
	return (res);
}

char	*here_expansion(t_mini *m, char *str, int x, int st)
{
	char	*res;

	res = NULL;
	while (str[x])
	{
		if (str[x] == '$' && is_valid_expansion(str[x + 1]))
		{
			if (st == x)
				res = here_expander(m, str, res, &x);
			else
				res = here_expander(m, str, p_ft_strjoin(m, \
					res, ft_strndup(m, str + st, x - st, 0)), &x);
			st = x;
		}
		else
			x++;
	}
	if (st != x)
	{
		if (!res)
			res = ft_strndup(m, str + st, x - st, 1);
		else
			res = p_ft_strjoin(m, res, ft_strndup(m, str + st, x - st, 0));
	}
	return (res);
}
