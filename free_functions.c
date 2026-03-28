/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oltolmac <oltolmac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 17:55:55 by johuber           #+#    #+#             */
/*   Updated: 2025/06/20 20:07:41 by oltolmac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

void	open_error(t_mini *mini, char *file)
{
	mini->exit = 1;
	if (file != NULL)
	{
		ft_putstr_fd(file, STDERR_FILENO);
		ft_putstr_fd(":", STDERR_FILENO);
	}
	if (errno == EACCES)
		ft_putendl_fd(" Permission denied", STDERR_FILENO);
	else if (errno == ENOENT)
	{
		ft_putendl_fd(" No such file or directory", STDERR_FILENO);
	}
	else if (errno == EISDIR)
		ft_putendl_fd(" Is a directory", STDERR_FILENO);
	else
		ft_putendl_fd(" Open Error!", STDERR_FILENO);
	free_exit_procces(mini, NULL);
}

void	dup_error(t_mini *mini)
{
	free_exit_procces(mini, "Dup Error!\n");
}

void	no_cmd_msg(t_mini *mini, char *name)
{
	ft_putstr_fd(name, STDERR_FILENO);
	ft_putstr_fd(": command not found", STDERR_FILENO);
	ft_putchar_fd('\n', STDERR_FILENO);
	mini->exit = 127;
	free_exit_procces(mini, NULL);
}

void	dupandclose(t_mini *mini, int o)
{
	if (o == 1)
	{
		if (dup2(mini->fd, STDIN_FILENO) == -1)
		{
			close(mini->fd);
			cl_fd(mini->pipefd);
			dup_error(mini);
		}
		close(mini->fd);
	}
	else if (o == 2)
	{
		close(mini->pipefd[0]);
		if (dup2(mini->pipefd[1], STDOUT_FILENO) == -1)
		{
			close(mini->fd);
			close(mini->pipefd[1]);
			dup_error(mini);
		}
		close(mini->pipefd[1]);
	}
}

void	m_ft_free_env(t_mini *mini, t_env *env)
{
	t_env	*tmp;

	tmp = env;
	while (tmp)
	{
		if (tmp->value)
			free(tmp->value);
		if (tmp->name)
			free(tmp->name);
		tmp = tmp->next;
	}
	while (env)
	{
		tmp = env;
		env = env->next;
		free(tmp);
	}
	rl_clear_history();
	close(mini->fd_in);
	close(mini->fd_out);
	exit(1);
}
