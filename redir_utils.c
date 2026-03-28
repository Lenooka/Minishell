/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oltolmac <oltolmac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 15:48:15 by oltolmac          #+#    #+#             */
/*   Updated: 2025/06/23 15:12:03 by oltolmac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

void	handle_redirag(t_mini *mini, char *file, char *token)
{
	if ((ft_strcmp(token, ">") == 0 && mini->l == 0)
		|| (ft_strcmp(token, ">>") == 0 && mini->l == 0))
	{
		if ((ft_strcmp(file, ">") == 0) || (ft_strcmp(file, ">>") == 0))
			mini->l = 1;
		redirect_out(token, file, mini);
	}
	else if ((ft_strcmp(token, "<") == 0 && mini->h == 0)
		|| (ft_strcmp(token, "<<") == 0 && mini->h == 0))
	{
		if (ft_strcmp(file, "<") == 0 || (ft_strcmp(file, "<<") == 0))
			mini->h = 1;
		redirect_in(token, file, mini);
	}
}

void	*path_lines(t_mini *mini, char *name)
{
	if (ft_strcmp(name, "<<") == 0 && mini->heredoc_flag == 1)
	{
		mini->exit = 0;
	}
	else
		no_cmd_msg(mini, name);
	return (NULL);
}
