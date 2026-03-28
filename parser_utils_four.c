/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils_four.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oltolmac <oltolmac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 19:11:49 by johuber           #+#    #+#             */
/*   Updated: 2025/06/08 16:11:44 by oltolmac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

int	is_no_tokens(char c)
{
	if (is_arrow(c) || c == '$' || is_space(c) \
		|| is_quote(c) || c == '|' || c == '\0')
		return (0);
	return (1);
}

void	make_cmd_no_redir(t_mini *mini, t_cmd *cmd)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	while (cmd->cmd_w_flags[x])
	{
		if (is_arrow(cmd->cmd_w_flags[x][0]))
		{
			x++;
			if (!cmd->cmd_w_flags[x++])
				break ;
			if (!cmd->cmd_w_flags[x])
				break ;
		}
		cmd->cmd_no_redir[y] = ft_strdup(cmd->cmd_w_flags[x]);
		if (!cmd->cmd_no_redir[y])
		{
			error_msg(mini, "🪐 MiniSheLL 🪐 : Malloc failure in tokenization\n");
			ft_parser_exit(mini, mini->msplit, mini->cmd_line, NULL);
		}
		y++;
		x++;
	}
	cmd->cmd_no_redir[y] = NULL;
}

int	get_token_no_token_size(char **str)
{
	int	x;
	int	count;

	count = 1;
	x = 0;
	while (str[x])
	{
		if (is_arrow(str[x][0]))
		{
			x++;
			if (str[x] == NULL)
				break ;
			x++;
			if (str[x] == NULL)
				break ;
		}
		x++;
		count++;
	}
	return (count);
}

char	*handle_question(t_mini *mini)
{
	char	*str;

	str = ft_itoa(mini->exit);
	if (!str)
	{
		error_msg(mini, "🪐 MiniSheLL 🪐 : Malloc failure in tokenization\n");
		ft_parser_exit(mini, mini->msplit, mini->cmd_line, NULL);
	}
	return (str);
}

int	quotes_msg(t_mini *mini, int quotes)
{
	if (quotes == 1)
		return (error_msg(mini, "🪐 MiniSheLL 🪐 : syntax error near " \
			"unexpected token `\"'\n"));
	else if (quotes == 2)
		return (error_msg(mini, "🪐 MiniSheLL 🪐 : syntax error near " \
			"unexpected token `\''\n"));
	return (1);
}
