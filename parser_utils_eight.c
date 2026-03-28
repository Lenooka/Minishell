/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils_eight.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oltolmac <oltolmac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 16:36:44 by oltolmac          #+#    #+#             */
/*   Updated: 2025/06/22 16:37:56 by oltolmac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

char	*m_handle_space_only(t_mini *mini, char *res)
{
	char	*tmp;

	tmp = ft_strdup(" ");
	if (!tmp)
	{
		error_msg(mini, "🪐 MiniSheLL 🪐 : Malloc failure in parsing\n");
		free(res);
		ft_parser_exit(mini, mini->msplit, mini->cmd_line, NULL);
	}
	tmp = p_ft_strjoin(mini, res, tmp);
	return (tmp);
}

void	parse_exp_allocat(t_mini *mini, t_cmd *cmd, char *str, char *res)
{
	cmd->free = str;
	mini->free = res;
}

void	parse_exp_deallocat(t_mini *mini, t_cmd *cmd)
{
	cmd->free = NULL;
	mini->free = NULL;
}

char	*parse_exp_tmp(t_mini *mini, t_cmd *cmd, char *tmp, int *x)
{
	char	*str;
	char	*res;
	int		start;

	str = cmd->free;
	res = mini->free;
	start = (*x);
	while (!is_space(str[(*x)]) && str[(*x)])
		(*x)++;
	if (tmp)
		cmd->cmd_w_flags[cmd->y++] = tmp;
	if (!tmp && start != 0)
		cmd->cmd_w_flags[cmd->y++] = res;
	tmp = ft_strndup(mini, str + start, (*x) - start, 1);
	if (start == 0)
		tmp = p_ft_strjoin(mini, res, tmp);
	return (tmp);
}
