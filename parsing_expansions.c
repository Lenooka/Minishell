/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_expansions.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oltolmac <oltolmac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 15:27:24 by johuber           #+#    #+#             */
/*   Updated: 2025/06/22 16:37:46 by oltolmac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

char	*parse_exp_merge(t_mini *mini, t_cmd *cmd, char *res, char *str)
{
	char	*tmp;
	int		x;

	x = skip_spaces(str, 0);
	if (!str[x])
		return (free(str), m_handle_space_only(mini, res));
	tmp = NULL;
	while (str[x])
	{
		if (!is_space(str[x]))
		{
			parse_exp_allocat(mini, cmd, str, res);
			tmp = parse_exp_tmp(mini, cmd, tmp, &x);
			parse_exp_deallocat(mini, cmd);
		}
		else
			x = skip_spaces(str, x);
	}
	if (is_space(str[x - 1]))
	{
		cmd->cmd_w_flags[cmd->y++] = tmp;
		return (free(str), NULL);
	}
	return (free(str), tmp);
}

void	handle_space_only(t_mini *mini, t_cmd *cmd, char *str0, char *str)
{
	char	*tmp;

	tmp = ft_strdup(" ");
	if (!tmp)
	{
		error_msg(mini, "🪐 MiniSheLL 🪐 : Malloc failure in parsing\n");
		ft_parser_exit(mini, mini->msplit, mini->cmd_line, str);
	}
	cmd->empty[cmd->y] = 2;
	if (str0[cmd->x] == '$'
		|| is_no_tokens(str0[cmd->x]) || is_quote(str0[cmd->x]))
	{
		free(str);
		handle_token_merge(mini, cmd, str0, tmp);
	}
	else
	{
		free(str);
		cmd->cmd_w_flags[cmd->y++] = tmp;
	}
}

int	check_spaces(char *str)
{
	int	x;

	x = skip_spaces(str, 0);
	while (!is_space(str[x]) && str[x])
		x++;
	if (!str[x])
		return (0);
	if (is_space(str[x]))
		x = skip_spaces(str, x);
	if (str[x])
		return (2);
	return (0);
}

char	*parse_exp_tmp_two(t_mini *mini, char *str, char *tmp, int *x)
{
	int		start;
	t_cmd	*cmd;

	cmd = get_last_node(mini->cmd);
	start = *x;
	while (!is_space(str[(*x)]) && str[(*x)])
		(*x)++;
	if (tmp)
		cmd->cmd_w_flags[cmd->y++] = tmp;
	tmp = ft_strndup(mini, str + start, (*x) - start, 1);
	return (tmp);
}

void	parse_exp(t_mini *mini, t_cmd *cmd, char *str0, char *str)
{
	char	*tmp;
	int		x;

	x = skip_spaces(str, 0);
	if (!str[x])
		return (handle_space_only(mini, cmd, str0, str));
	tmp = NULL;
	cmd->empty[cmd->y] = check_spaces(str);
	while (str[x])
	{
		if (!is_space(str[x]))
			tmp = parse_exp_tmp_two(mini, str, tmp, &x);
		else
			x = skip_spaces(str, x);
	}
	if (!is_space(str[x - 1]) && (str0[cmd->x] == '$'
			|| is_no_tokens(str0[cmd->x]) || is_quote(str0[cmd->x])))
	{
		handle_token_merge(mini, cmd, str0, tmp);
		return (free(str));
	}
	return (cmd->cmd_w_flags[cmd->y++] = tmp, free(str));
}
