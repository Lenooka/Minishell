/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_prep.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oltolmac <oltolmac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 19:20:17 by johuber           #+#    #+#             */
/*   Updated: 2025/06/22 14:28:03 by johuber          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

int	pipe_checks(char *str)
{
	int	x;

	x = skip_spaces(str, 0);
	if (str[x] == '|')
		return (1);
	if (is_quote(str[x]))
		x = skip_quotes(str, x);
	while (str[x])
	{
		if (str[x] == '|')
		{
			x++;
			if (str[x] == '|')
				return (1);
		}
		if (is_quote(str[x]))
			x = skip_quotes(str, x);
		if (str[x])
			x++;
	}
	x = rev_skip_spaces(str, x - 1);
	if (str[x] == '|')
		return (1);
	return (0);
}

int	quote_check(char *str, int squotes, int dquotes)
{
	int	x;

	x = 0;
	while (str[x])
	{
		if (is_dquote(str[x]))
		{
			dquotes++;
			x = skip_dquote(str, x, &dquotes);
		}
		else if (is_squote(str[x]))
		{
			squotes++;
			x = skip_squote(str, x, &squotes);
		}
		else if (str[x])
			x++;
	}
	if (dquotes % 2 == 1)
		return (1);
	if (squotes % 2 == 1)
		return (2);
	return (0);
}

t_cmd	*make_cmd_list(t_mini *mini, int x)
{
	t_cmd	*tmp;
	t_cmd	*origin;

	origin = mini->cmd;
	tmp = (t_cmd *)malloc(sizeof(t_cmd));
	if (tmp == NULL)
		return (NULL);
	tmp->cmd_w_flags = NULL;
	tmp->cmd_no_redir = NULL;
	tmp->empty = NULL;
	tmp->free = NULL;
	tmp->path = NULL;
	tmp->redir = 0;
	tmp->x = 0;
	tmp->y = 0;
	tmp->name = NULL;
	tmp->next = NULL;
	if (x == 0)
		return (tmp);
	while (origin->next != NULL)
		origin = origin->next;
	origin->next = tmp;
	return (mini->cmd);
}

int	multiple_parsing_prep(char **str, t_mini *mini)
{
	int		x;
	t_cmd	*tmp;
	char	**tokens;

	x = 0;
	while (str[x])
	{
		tmp = make_cmd_list(mini, x);
		if (skip_spaces(str[x], 0) == (int)ft_strlen(str[x]))
			return (ft_empty_pipe(mini, tmp, str, 0), 1);
		tokens = calc_tokens(mini, str[x], tmp);
		if (tmp == NULL || !tokens || !tmp->empty)
		{
			ft_empty_pipe(mini, tmp, str, 1);
			ft_parser_exit(mini, tokens, mini->cmd_line, NULL);
		}
		mini->cmd = tmp;
		tmp = get_last_node(tmp);
		tmp->cmd_w_flags = tokens;
		if (multiple_parsing(mini, str[x], tmp))
			return (ft_free_cmd(mini), free_2d_array(str), 1);
		x++;
	}
	mini->ret = heredoc_check(mini, mini->cmd);
	return (free_2d_array(str), mini->msplit = NULL, mini->ret);
}

int	wrong_parsing(t_mini *mini, char *str)
{
	char	**res;
	int		quotes;

	res = NULL;
	mini->skip = 0;
	if (pipe_checks(str))
		return (error_msg(mini, "🪐 MiniSheLL 🪐 : syntax error near " \
		"unexpected token `|'\n"));
	quotes = quote_check(str, 0, 0);
	if (quotes == 1)
		return (error_msg(mini, "🪐 MiniSheLL 🪐 : syntax error near " \
		"unexpected token `\"'\n"));
	else if (quotes == 2)
		return (error_msg(mini, "🪐 MiniSheLL 🪐 : syntax error near " \
		"unexpected token `\''\n"));
	if (is_pipe(str))
	{
		res = ft_msplit(str, '|');
		if (res == NULL)
			return (m_ft_free_env(mini, mini->env), free(mini->cmd_line), 1);
	}
	else
		return (single_parsing_prep(str, mini));
	mini->msplit = res;
	return (multiple_parsing_prep(res, mini));
}
