/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oltolmac <oltolmac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 12:03:39 by oltolmac          #+#    #+#             */
/*   Updated: 2025/06/20 19:13:15 by oltolmac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

void	print_list(t_env *env_list)
{
	while (env_list->next)
	{
		printf("name %s\n", env_list->name);
		printf("val %s\n", env_list->value);
		env_list = env_list->next;
	}
}

char	*find_default(t_env *envl)
{
	while (envl)
	{
		if (ft_strcmp((envl)->name, "HOME") == 0)
			return ((envl)->value);
		envl = (envl)->next;
	}
	return (NULL);
}

int	is_built(char *cmd)
{
	if (ft_strcmp(cmd, "echo") == 0)
		return (1);
	else if (ft_strcmp(cmd, "cd") == 0)
		return (1);
	else if (ft_strcmp(cmd, "pwd") == 0)
		return (1);
	else if (ft_strcmp(cmd, "export") == 0)
		return (1);
	else if (ft_strcmp(cmd, "unset") == 0)
		return (1);
	else if (ft_strcmp(cmd, "env") == 0)
		return (1);
	else if (ft_strcmp(cmd, "exit") == 0)
		return (1);
	return (0);
}

void	run_builtwo(t_mini *mini, t_cmd *cmds, char *cmd)
{
	mini->b_ex = 0;
	if (ft_strcmp(cmd, "echo") == 0)
		ft_echo(cmds->cmd_w_flags);
	else if (ft_strcmp(cmd, "cd") == 0)
		ft_cd(mini, cmds->cmd_w_flags);
	else if (ft_strcmp(cmd, "pwd") == 0)
		ft_pwd();
	else if (ft_strcmp(cmd, "export") == 0)
		ft_export(mini, cmds->cmd_w_flags);
	else if (ft_strcmp(cmd, "unset") == 0)
		ft_unset(mini, cmds->cmd_w_flags);
	else if (ft_strcmp(cmd, "env") == 0)
		ft_env(mini);
	else if (ft_strcmp(cmd, "exit") == 0)
		ft_exit(mini, cmds->cmd_w_flags);
	mini->b_ex = 1;
	return ;
}

void	run_built(t_mini *m, t_cmd *cmds, char *cmd)
{
	m->b_ex = 0;
	m->exit = 0;
	if (cmds->redir == 0)
		return (run_builtwo(m, cmds, cmd));
	cmds->cmd_no_redir = clean_cmd(cmds->cmd_no_redir, m->heredoc_flag, m);
	if (ft_strcmp(cmd, "echo") == 0)
		ft_echo(cmds->cmd_no_redir);
	else if (ft_strcmp(cmd, "cd") == 0)
		ft_cd(m, cmds->cmd_no_redir);
	else if (ft_strcmp(cmd, "pwd") == 0)
		ft_pwd();
	else if (ft_strcmp(cmd, "export") == 0)
		ft_export(m, cmds->cmd_no_redir);
	else if (ft_strcmp(cmd, "unset") == 0)
		ft_unset(m, cmds->cmd_no_redir);
	else if (ft_strcmp(cmd, "env") == 0)
		ft_env(m);
	else if (ft_strcmp(cmd, "exit") == 0)
		ft_exit(m, cmds->cmd_no_redir);
	m->b_ex = 1;
	return ;
}
