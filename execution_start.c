/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_start.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oltolmac <oltolmac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 18:12:46 by oltolmac          #+#    #+#             */
/*   Updated: 2025/06/23 14:55:13 by oltolmac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

void	run_parent_exec(t_mini *mini, int i)
{
	if (i > 0)
		close(mini->fd);
	if (i < mini->cmd_am - 1)
	{
		close(mini->pipefd[1]);
		mini->fd = mini->pipefd[0];
	}
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
}

void	run_child_exec(t_mini *mini, char **env, t_cmd *c, int i)
{
	signal(SIGPIPE, signal_global);
	signal(SIGQUIT, SIG_DFL);
	signal(SIGINT, SIG_DFL);
	mini->exit = 0;
	if (i > 0)
		dupandclose(mini, 1);
	if (i < mini->cmd_am - 1)
		dupandclose(mini, 2);
	if (c->redir == 1)
		handle_redir(mini, c);
	if (array_is_empty(mini, c, c->cmd_w_flags))
		free_exit_procces(mini, NULL);
	if (c->redir == 1)
		c->cmd_w_flags = clean_cmd(c->cmd_w_flags, mini->heredoc_flag, mini);
	if (!c->cmd_w_flags)
	{
		mini->exit = 1;
		free_exit_procces(mini, NULL);
	}
	mini->benv = build_envp(mini, mini->env);
	if (!mini->benv)
		free_exit_procces(mini, "Error: Malloc fail in envp");
	exec_cmd_call(mini, c->cmd_w_flags, c, env);
}

int	run_one_built(t_mini *mini, t_cmd *cmd)
{
	if (mini->cmd_am == 1 && is_built(cmd->name) && mini->heredoc_flag == 0)
	{
		if (cmd->redir == 0)
		{
			run_built(mini, cmd, cmd->name);
			ft_free_cmd(mini);
			dup2(mini->fd_in, STDIN_FILENO);
			dup2(mini->fd_out, STDOUT_FILENO);
			mini->b_ex = 0;
			return (1);
		}
	}
	return (0);
}

void	clean_up(t_mini *mini)
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
}

void	minishell_execution_start(t_mini *mini, char **env)
{
	pid_t	pid;
	t_cmd	*cmd;

	mini->i = 0;
	mini->cmd_am = ft_lstsizexec(mini->cmd);
	cmd = mini->cmd;
	if (run_one_built(mini, cmd))
		return ;
	while (mini->i < mini->cmd_am)
	{
		if (mini->i < mini->cmd_am - 1 && pipe(mini->pipefd) == -1)
			free_exit_procces(mini, "Error: Pipe fail 🐸");
		pid = fork();
		if (pid == -1)
			free_exit_procces(mini, "Error: Fork fail");
		else if (pid == 0)
			run_child_exec(mini, env, cmd, mini->i);
		else
			run_parent_exec(mini, mini->i);
		mini->i++;
		if (cmd->next != NULL)
			cmd = cmd->next;
	}
	exit_status(mini, pid, mini->cmd_am);
	clean_up(mini);
}
