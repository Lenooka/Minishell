/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_merge.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oltolmac <oltolmac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 16:38:08 by johuber           #+#    #+#             */
/*   Updated: 2025/06/20 20:08:00 by oltolmac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

char	*m_handle_quote_exp(t_mini *mini, t_cmd *cmd, char *str, int start)
{
	char	*tmp;

	tmp = NULL;
	while (str[cmd->x] && !is_dquote(str[cmd->x]))
	{
		if (str[cmd->x] == '$'
			&& (is_valid_expansion(str[cmd->x + 1]) || str[cmd->x + 1] == '?'))
		{
			if (start == cmd->x)
				only_expansion(mini, str, &tmp, &start);
			else
				char_expansion(mini, str, &tmp, &start);
		}
		else
			cmd->x++;
	}
	if (start != cmd->x)
		tmp = p_ft_strjoin(mini, tmp,
				ft_strndup(mini, str + start, cmd->x - start, 0));
	if (str[cmd->x])
		cmd->x++;
	return (tmp);
}

char	*handle_quote_merge(t_mini *mini, t_cmd *cmd, char *str, char *res)
{
	char	*tmp;
	int		start;

	tmp = NULL;
	cmd->free = res;
	if (is_squote(str[cmd->x]))
	{
		cmd->x++;
		start = cmd->x;
		while (!is_squote(str[cmd->x]) && str[cmd->x])
			cmd->x++;
		tmp = ft_strndup(mini, str + start, cmd->x - start, 1);
		cmd->x++;
	}
	else if (is_dquote(str[cmd->x]))
	{
		cmd->x++;
		start = cmd->x;
		if (is_dquote(str[cmd->x]))
			return (cmd->free = NULL,
				cmd->x++, p_ft_strjoin(mini, res, ft_strdup("")));
		tmp = m_handle_quote_exp(mini, cmd, str, start);
	}
	cmd->free = NULL;
	return (p_ft_strjoin(mini, res, tmp));
}

char	*m_merge_char(t_mini *mini, t_cmd *cmd, char *str, char *res)
{
	int		start;
	char	*tmp;

	start = cmd->x;
	while (str[cmd->x] && is_no_tokens(str[cmd->x]))
		cmd->x++;
	mini->free = res;
	tmp = ft_strndup(mini, str + start, cmd->x - start, 1);
	mini->free = NULL;
	res = p_ft_strjoin(mini, res, tmp);
	return (res);
}

char	*m_handle_dol(t_mini *mini, t_cmd *cmd, char *res, char *str)
{
	char	*tmp;

	tmp = NULL;
	mini->free = res;
	if (!is_valid_expansion(str[cmd->x + 1]) && str[cmd->x + 1] != '?')
		tmp = dol_empty_expansion(mini, cmd, str);
	else
	{
		tmp = get_env_value(mini, mini->env, get_env_name(mini, str, cmd->x));
		if (has_space(tmp))
		{
			mini->free = NULL;
			tmp = parse_exp_merge(mini, cmd, res, tmp);
			skip_expansion(cmd, str);
			return (tmp);
		}
		skip_expansion(cmd, str);
	}
	mini->free = NULL;
	if (tmp)
		res = p_ft_strjoin(mini, res, tmp);
	return (res);
}

char	*handle_token_merge(t_mini *mini, t_cmd *cmd, char *str, char *res)
{
	if (str[cmd->x] == '$')
	{
		res = m_handle_dol(mini, cmd, res, str);
		if (!res)
			return (NULL);
	}
	else if (is_no_tokens(str[cmd->x]))
		res = m_merge_char(mini, cmd, str, res);
	else if (is_quote(str[cmd->x]))
		res = handle_quote_merge(mini, cmd, str, res);
	if (str[cmd->x] == '$' || is_no_tokens(str[cmd->x]) \
		|| is_quote(str[cmd->x]))
		handle_token_merge(mini, cmd, str, res);
	else
		cmd->cmd_w_flags[cmd->y++] = res;
	return (NULL);
}
