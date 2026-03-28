/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   single_parsing.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oltolmac <oltolmac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 16:52:50 by johuber           #+#    #+#             */
/*   Updated: 2025/06/20 21:00:51 by oltolmac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

int	single_parsing(t_mini *mini, char *str, t_cmd *cmd)
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

int	single_parsing_prep(char *str, t_mini *mini)
{
	char	**tokens;

	mini->cmd = make_cmd_list(mini, 0);
	if (skip_spaces(str, 0) == (int)ft_strlen(str))
		return (ft_free_cmd(mini), 1);
	tokens = calc_tokens(mini, str, mini->cmd);
	if (mini->cmd == NULL || !tokens || !mini->cmd->empty)
	{
		error_msg(mini, "🪐 MiniSheLL 🪐 : Malloc failure in parsing\n");
		ft_parser_exit(mini, tokens, str, NULL);
	}
	mini->cmd->cmd_w_flags = tokens;
	if (single_parsing(mini, str, mini->cmd))
		return (ft_free_cmd(mini), 1);
	if (heredoc_check(mini, mini->cmd) == 1)
		return (ft_free_cmd(mini), 1);
	return (0);
}
