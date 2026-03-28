/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oltolmac <oltolmac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 19:12:20 by johuber           #+#    #+#             */
/*   Updated: 2025/06/23 15:17:13 by oltolmac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

void	shift_cmd(char **cmd, int i)
{
	i = i + 2;
	while (cmd[i])
	{
		cmd[i] = cmd[i + 1];
		i++;
	}
}

void	replace_cmd(char **cmd, int heredoc_flag, t_mini *mini, int i)
{
	if (ft_strcmp(cmd[0], "<<") == 0 && cmd[i + 1] && cmd[i + 2])
	{
		free(cmd[0]);
		cmd[i] = ft_strdup(cmd[i + 2]);
		if (!cmd[i])
			free_exit_procces(mini, "Malloc fail!\n");
		free(cmd[i + 2]);
		if (!cmd[i + 3])
			cmd[i + 2] = NULL;
		else
			return (shift_cmd(cmd, i));
	}
	while (cmd[i])
	{
		if (heredoc_flag == 1 && ft_strcmp(cmd[i], "<<") == 0 && cmd[i + 1])
		{
			free(cmd[i]);
			cmd[i] = ft_strdup(mini->heredoc_buf);
			if (!cmd[i])
				free_exit_procces(mini, "Malloc fail!\n");
			free(cmd[i + 1]);
			cmd[i + 1] = NULL;
		}
		i++;
	}
}

int	is_redir(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (ft_strcmp(str[i], "<") == 0 || ft_strcmp(str[i], ">") == 0
			|| ft_strcmp(str[i], ">>") == 0 || ft_strcmp(str[i], "<<") == 0)
			return (1);
		i++;
	}
	return (0);
}

void	redirect_out(char *oper, char *file, t_mini *mini)
{
	if (ft_strcmp(oper, ">>") == 0)
	{
		appredirout_sys(file, mini);
	}
	else if ((ft_strcmp(oper, ">") == 0))
	{
		redirout_sys(file, mini);
	}
}

void	redirect_in(char *oper, char *file, t_mini *mini)
{
	if (ft_strcmp(oper, "<<") == 0)
		heredoc_redir(file, mini);
	else if ((ft_strcmp(oper, "<") == 0))
		redirin_sys(file, mini);
}
