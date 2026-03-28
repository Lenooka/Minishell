/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olena <olena@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 14:45:41 by oltolmac          #+#    #+#             */
/*   Updated: 2025/07/05 18:07:12 by olena            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

int	g_global = 0;

void	def_struct_vals(t_mini *mini, char **envp)
{
	if (array_is_envmpty(envp))
	{
		ft_putstr_fd("Enviroment variables list is empty!\n", STDERR_FILENO);
		exit(1);
	}
	mini->end = 1;
	mini->fd = -1;
	mini->env = NULL;
	mini->b_ex = 0;
	mini->cmd_am = 0;
	mini->msplit = NULL;
	mini->free = NULL;
	mini->cmd = NULL;
	mini->heredoc_flag = 0;
	mini->i = 0;
	mini->heredoc_buf = NULL;
	mini->size = sizeofarry(envp);
	env_define(mini, envp);
	mini->fd_in = dup(STDIN_FILENO);
	if (mini->fd_in == -1)
		exit(1);
	mini->fd_out = dup(STDOUT_FILENO);
	if (mini->fd_out == -1)
		exit(1);
	mini->exit = 0;
}

void	loop_break_free(t_mini *mini)
{
	rl_clear_history();
	handler_ctrl_d(mini);
	exit(mini->exit);
}

void	make_sigaction(void)
{
	struct sigaction	sa;

	sa.sa_sigaction = &handle_sigint;
	sa.sa_flags = SA_SIGINFO | SA_RESTART;
	sigemptyset(&(sa.sa_mask));
	sigaction(SIGINT, &sa, NULL);
	signal(SIGQUIT, SIG_IGN);
}

int	minishell(t_mini *mini)
{
	make_sigaction();
	mini->cmd_line = readline("🪐 MiniSheLL 🪐 : ");
	if (!mini->cmd_line)
	{
		if (g_global == 130)
		{
			mini->exit = 130;
			g_global = 0;
		}
		return (0);
	}
	if (g_global == 130)
	{
		mini->exit = 130;
		g_global = 0;
	}
	if (ft_strlen(mini->cmd_line))
		add_history(mini->cmd_line);
	if (!(mini->cmd_line[0]) || wrong_parsing(mini, mini->cmd_line))
		return (1);
	return (2);
}

int	main(int argc, char **argv, char **envp)
{
	t_mini	mini;
	int		status;

	if (argc != 1)
		return (1);
	def_struct_vals(&mini, envp);
	while (mini.end && !argv[1])
	{
		if (mini.shlvl == 1)
			decrs_shlvl(&mini);
		status = minishell(&mini);
		if (status == 0)
			break ;
		if (status == 1)
			continue ;
		if (status == 2)
		{
			if (ft_strcmp(mini.cmd->name, "./minishell") == 0
				|| ft_strcmp(mini.cmd->name, "bash") == 0)
				adjust_shlvl(&mini);
			minishell_execution_start(&mini, envp);
		}
	}
	loop_break_free(&mini);
	return (0);
}
