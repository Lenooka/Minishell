/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_two.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oltolmac <oltolmac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/08 17:53:17 by oltolmac          #+#    #+#             */
/*   Updated: 2025/06/17 14:29:56 by oltolmac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

void	free_exit_heredoc(t_mini *mini, char *str, char *fr_a)
{
	int	status;

	status = mini->exit;
	if (fr_a)
		free(fr_a);
	if (str != NULL)
		ft_putstr_fd(str, STDERR_FILENO);
	free(mini->heredoc_buf);
	if (mini->msplit)
		free_2d_array(mini->msplit);
	if (mini->cmd_line)
		free(mini->cmd_line);
	if (mini->cmd)
	{
		ft_free_cmd(mini);
		mini->cmd = NULL;
	}
	ft_free_env(mini->env);
	rl_clear_history();
	mini->env = NULL;
	close(mini->fd_in);
	close(mini->fd_out);
	close(mini->here_fd);
	exit(status);
}

int	count_split(char *str, char sep)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] == sep && i != 0)
			count++;
		i++;
	}
	count++;
	return (count);
}

char	**free_arr_back(char **str, int i)
{
	int	a;

	a = 0;
	while (a < i && str[a] != NULL)
	{
		free(str[a]);
		a++;
	}
	free(str);
	return (NULL);
}
