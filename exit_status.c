/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_status.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oltolmac <oltolmac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 13:58:25 by oltolmac          #+#    #+#             */
/*   Updated: 2025/06/22 20:14:24 by oltolmac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

void	cl_fd(int *pipefd)
{
	close(pipefd[0]);
	close(pipefd[1]);
}

void	reset_fd(t_mini *minsh)
{
	if (dup2(minsh->fd_in, STDIN_FILENO) == -1)
		free_exit_procces(minsh, NULL);
	if (dup2(minsh->fd_out, STDOUT_FILENO) == -1)
		free_exit_procces(minsh, NULL);
	minsh->heredoc_flag = 0;
}

void	exit_status(t_mini *mini, pid_t last, int com_run)
{
	int		status;
	pid_t	wpid;

	mini->i = 0;
	while (mini->i++ < com_run)
	{
		wpid = wait(&status);
		if (wpid == -1)
			break ;
		if (wpid == last)
		{
			if (WIFEXITED(status))
				mini->exit = WEXITSTATUS(status);
			else if (WIFSIGNALED(status))
			{
				if (WTERMSIG(status) == SIGINT)
					write(1, "\n", 1);
				mini->exit = 128 + WTERMSIG(status);
				if (mini->exit == 131)
					ft_putstr_fd("Quit (core dumped)\n", 2);
			}
		}
	}
	reset_fd(mini);
	ft_free_cmd(mini);
}
