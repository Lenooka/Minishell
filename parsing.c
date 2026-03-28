/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oltolmac <oltolmac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 18:01:15 by johuber           #+#    #+#             */
/*   Updated: 2025/06/22 15:42:21 by oltolmac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

void	parse_heredoc_ident(t_mini *mini, t_cmd *cmd, char *str)
{
	int	start;

	cmd->x = skip_spaces(str, cmd->x);
	start = cmd->x;
	while (str[cmd->x] && !is_space(str[cmd->x]) && !is_arrow(str[cmd->x]))
	{
		if (is_dquote(str[cmd->x]))
		{
			cmd->x++;
			while (!is_dquote(str[cmd->x]))
				cmd->x++;
			cmd->x++;
		}
		else if (is_squote(str[cmd->x]))
		{
			cmd->x++;
			while (!is_squote(str[cmd->x]))
				cmd->x++;
			cmd->x++;
		}
		else
			cmd->x++;
	}
	cmd->cmd_w_flags[cmd->y++] = ft_strndup(mini, str + start,
			cmd->x - start, 1);
}

int	parse_arrow(t_mini *mini, t_cmd *cmd, char *str)
{
	char	*tmp;
	int		start;

	cmd->redir = 1;
	if (str[cmd->x] == '>')
	{
		start = cmd->x++;
		if (str[cmd->x] == '>')
			cmd->x++;
		if (check_arrow_error(mini, cmd, str))
			return (1);
		tmp = ft_strndup(mini, str + start, cmd->x - start, 1);
		cmd->cmd_w_flags[cmd->y++] = tmp;
		return (0);
	}
	start = cmd->x++;
	if (str[cmd->x] == '<')
		cmd->x++;
	if (check_arrow_error(mini, cmd, str))
		return (1);
	tmp = ft_strndup(mini, str + start, cmd->x - start, 1);
	cmd->cmd_w_flags[cmd->y++] = tmp;
	if (ft_strcmp(tmp, "<<") == 0)
		parse_heredoc_ident(mini, cmd, str);
	return (0);
}

void	parse_char(t_mini *mini, t_cmd *cmd, char *str)
{
	int		start;
	char	*tmp;

	start = cmd->x;
	while (str[cmd->x])
	{
		if (is_arrow(str[cmd->x]) || is_quote(str[cmd->x])
			|| is_space(str[cmd->x]) || str[cmd->x] == '$')
			break ;
		cmd->x++;
	}
	tmp = ft_strndup(mini, str + start, cmd->x - start, 1);
	if (str[cmd->x] == '$' || is_no_tokens(str[cmd->x]) \
		|| is_quote(str[cmd->x]))
		handle_token_merge(mini, cmd, str, tmp);
	else
		cmd->cmd_w_flags[cmd->y++] = tmp;
}

void	set_tokens(t_mini *mini, t_cmd *cmd)
{
	if (cmd->cmd_w_flags[0] == NULL)
		return ;
	cmd->name = ft_strdup(cmd->cmd_w_flags[0]);
	if (!cmd->name)
	{
		error_msg(mini, "🪐 MiniSheLL 🪐 : Malloc failure in tokenization\n");
		ft_parser_exit(mini, mini->msplit, mini->cmd_line, NULL);
	}
	cmd->cmd_no_redir = (char **)malloc(get_token_no_token_size(
				cmd->cmd_w_flags) * sizeof(char **));
	if (!cmd->cmd_no_redir)
	{
		error_msg(mini, "🪐 MiniSheLL 🪐 : Malloc failure in tokenization\n");
		ft_parser_exit(mini, mini->msplit, mini->cmd_line, NULL);
	}
	make_cmd_no_redir(mini, cmd);
}

int	multiple_parsing(t_mini *mini, char *str, t_cmd *cmd)
{
	int	quotes;

	quotes = quote_check(str, 0, 0);
	if (quotes != 0)
		return (quotes_msg(mini, quotes));
	cmd->x = skip_spaces(str, 0);
	while (str[cmd->x])
	{
		if (is_quote(str[cmd->x]))
			go_inquote(mini, cmd, str);
		else if (str[cmd->x] == '$')
			dol_expansion(mini, cmd, str);
		else if (is_arrow(str[cmd->x]))
		{
			if (parse_arrow(mini, cmd, str))
				return (cmd->cmd_w_flags[cmd->y] = NULL, 1);
		}
		else if (!is_space(str[cmd->x]))
			parse_char(mini, cmd, str);
		if (is_space(str[cmd->x]))
			cmd->x = skip_spaces(str, cmd->x);
	}
	cmd->cmd_w_flags[cmd->y] = NULL;
	set_tokens(mini, cmd);
	return (0);
}
