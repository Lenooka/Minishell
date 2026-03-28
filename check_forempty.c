/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_forempty.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oltolmac <oltolmac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/08 17:37:39 by oltolmac          #+#    #+#             */
/*   Updated: 2025/06/22 14:47:06 by oltolmac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

void	shift_if_empty(char **argv)
{
	int	i;

	if (!argv || !argv[0] || argv[0][0] != '\0')
		return ;
	i = 0;
	free(argv[i]);
	while (argv[i])
	{
		argv[i] = argv[i + 1];
		i++;
	}
}

int	is_all_dollars(const char *str)
{
	int	i;

	i = 0;
	if (!str || str[0] == '\0')
		return (0);
	while (str[i])
	{
		if (str[i] != '$')
			return (0);
		i++;
	}
	return (1);
}

int	check_emptyint(t_mini *mini, t_cmd *cmd, char **array)
{
	if (!array || !array[0] || (array[0][0] == '\0' && cmd->empty[0] == 0))
	{
		if (array[0][0] == '\0')
		{
			if (cmd->empty[0] == 0)
				no_cmd_msg(mini, "''");
		}
		mini->exit = 0;
		return (1);
	}
	return (0);
}

int	array_is_empty(t_mini *mini, t_cmd *cmd, char **array)
{
	int	i;

	i = 0;
	if (check_emptyint(mini, cmd, array) == 1)
		return (1);
	while (array[i])
	{
		if (array[i][0] != '\0')
		{
			if (cmd != NULL)
			{
				if (cmd->name)
					free(cmd->name);
				cmd->name = ft_strdup(array[i]);
				shift_if_empty(cmd->cmd_w_flags);
				shift_if_empty(cmd->cmd_no_redir);
				shift_if_empty(array);
			}
			return (0);
		}
		i++;
	}
	return (1);
}

int	array_is_envmpty(char **array)
{
	if (!array || !array[0])
		return (1);
	return (0);
}
