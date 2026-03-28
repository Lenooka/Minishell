/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oltolmac <oltolmac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 14:19:19 by johuber           #+#    #+#             */
/*   Updated: 2025/06/20 21:00:47 by oltolmac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

void	char_expansion(t_mini *mini, char *str, char **tmp, int *start)
{
	t_cmd	*cmd;
	char	*env;

	cmd = get_last_node(mini->cmd);
	if (*tmp)
		*tmp = p_ft_strjoin(mini,
				*tmp, ft_strndup(mini, str + *start, cmd->x - *start, 0));
	else
		*tmp = ft_strndup(mini, str + *start, cmd->x - *start, 1);
	mini->free = *tmp;
	env = get_env_value(mini, mini->env, get_env_name(mini, str, cmd->x));
	mini->free = NULL;
	*tmp = p_ft_strjoin(mini, *tmp, env);
	skip_expansion(cmd, str);
	*start = cmd->x;
}

void	only_expansion(t_mini *mini, char *str, char **tmp, int *start)
{
	t_cmd	*cmd;
	char	*env;

	cmd = get_last_node(mini->cmd);
	mini->free = *tmp;
	env = get_env_value(mini, mini->env, get_env_name(mini, str, cmd->x));
	mini->free = NULL;
	if (!*tmp)
		*tmp = env;
	else
		*tmp = p_ft_strjoin(mini, *tmp, env);
	skip_expansion(cmd, str);
	*start = cmd->x;
}

char	*quote_expansion(t_mini *mini, t_cmd *cmd, char *str, int start)
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

void	handle_squote(t_mini *mini, t_cmd *cmd, char *str, int start)
{
	while (!is_squote(str[cmd->x]) && str[cmd->x])
		cmd->x++;
	if (str[cmd->x + 1] == '$' || is_no_tokens(str[cmd->x + 1]) \
		|| is_quote(str[cmd->x + 1]))
	{
		cmd->x++;
		handle_token_merge(mini, cmd, str, \
			ft_strndup(mini, str + start, cmd->x - start - 1, 1));
		return ;
	}
	cmd->cmd_w_flags[cmd->y] = ft_strndup(mini, str + start, cmd->x - start, 1);
	if (cmd->cmd_w_flags[cmd->y] == NULL)
	{
		error_msg(mini, "🪐 MiniSheLL 🪐 : Malloc failure in tokenization\n");
		ft_parser_exit(mini, mini->msplit, mini->cmd_line, NULL);
	}
	cmd->y++;
	cmd->x++;
}

void	go_inquote(t_mini *mini, t_cmd *cmd, char *str)
{
	int		start;
	char	*tmp;

	if (is_squote(str[cmd->x]))
	{
		cmd->x++;
		start = cmd->x;
		handle_squote(mini, cmd, str, start);
		return ;
	}
	cmd->x++;
	start = cmd->x;
	if (is_dquote(str[cmd->x]))
		tmp = handle_empty_dquote(mini, cmd);
	else
		tmp = quote_expansion(mini, cmd, str, start);
	if (str[cmd->x] == '$' || is_no_tokens(str[cmd->x]) \
		|| is_quote(str[cmd->x]))
		handle_token_merge(mini, cmd, str, tmp);
	else
		cmd->cmd_w_flags[cmd->y++] = tmp;
}
