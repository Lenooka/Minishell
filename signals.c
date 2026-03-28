/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oltolmac <oltolmac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 15:25:11 by oltolmac          #+#    #+#             */
/*   Updated: 2025/06/19 16:08:35 by oltolmac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

void	heredoc_signal_handle(int signal)
{
	if (signal == SIGINT)
	{
		g_global = SIGINT;
		write(STDIN_FILENO, "\n", 1);
		close(STDIN_FILENO);
	}
}

void	handle_sigint(int signum, siginfo_t *info, void *context)
{
	(void)context;
	(void)info;
	if (signum == SIGINT)
	{
		g_global = 130;
		write(STDOUT_FILENO, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	signal_global(int signum)
{
	if (signum == SIGQUIT)
	{
		g_global = SIGQUIT;
	}
	if (signum == SIGINT)
	{
		g_global = SIGINT;
	}
}

void	handler_ctrl_d(t_mini *mini)
{
	if (mini->cmd_line)
	{
		free(mini->cmd_line);
		mini->cmd_line = NULL;
	}
	if (mini->cmd)
	{
		ft_free_cmd(mini);
		mini->cmd = NULL;
	}
	if (!(mini->cmd_line))
		printf("exit\n");
	if (mini->env)
		ft_free_env(mini->env);
	if (mini->heredoc_buf)
		free(mini->heredoc_buf);
	close(mini->fd_in);
	close(mini->fd_out);
}

void	check_global_end(void)
{
	if (!g_global)
		return ;
	if (g_global == SIGQUIT)
		ft_putstr_fd("exit\n", 2);
	if (g_global == SIGINT)
		printf("\n");
	g_global = 0;
}
