/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oltolmac <oltolmac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 18:41:45 by jhuber            #+#    #+#             */
/*   Updated: 2025/06/20 19:20:07 by oltolmac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

void	change_oldpath(t_env *envl, char *oldpath)
{
	char	*new_content;
	int		x;

	x = 0;
	while (envl && !x)
	{
		if (ft_strcmp((envl)->name, "OLDPWD") == 0)
		{
			new_content = ft_strdup(oldpath);
			free((envl)->value);
			(envl)->value = new_content;
			x++;
		}
		if (!x)
			envl = (envl)->next;
	}
}

void	change_path(t_env *envl, char *oldpath)
{
	t_env	*tmp;
	char	newpath[4096 + 1];
	int		x;

	x = 0;
	tmp = envl;
	while (envl && !x)
	{
		if (ft_strcmp((envl)->name, "PWD") == 0)
		{
			getcwd(newpath, sizeof(newpath));
			free((envl)->value);
			(envl)->value = ft_strdup(newpath);
			ft_bzero(newpath, ft_strlen(newpath));
			x++;
		}
		if (!x)
			envl = (envl)->next;
	}
	change_oldpath(tmp, oldpath);
}

void	enter_dir(t_mini *mini, char *env)
{
	size_t	len;
	int		x;
	char	*new_env;

	len = ft_strlen(env);
	new_env = ft_substr(env, 2, len - 2);
	x = chdir(new_env);
	if (x == -1)
	{
		error_msg_b(mini, " : No such file or directory", 1, "cd");
		mini->exit = 1;
	}
	if (!new_env)
		return ;
	free(new_env);
}

void	cd_default(t_mini *mini)
{
	char	*def;
	int		x;

	x = 0;
	if (mini->env == NULL)
		return ;
	def = find_default(mini->env);
	if (!def)
		error_msg_b(mini, " : Home not set", 1, "cd");
	else
		x = chdir(def);
	if (x == -1)
	{
		error_msg_b(mini, " : No such file or directory", 1, "cd");
		mini->exit = 1;
	}
}

void	ft_cd(t_mini *mini, char **env)
{
	char	oldenv[4096 + 1];

	getcwd(oldenv, sizeof(oldenv));
	if (env && sizeofarry(env) > 2)
	{
		error_msg_b(mini, " : too many arguments", 1, "cd");
		mini->exit = 1;
		return ;
	}
	if (!env || !env[1] || !env[1][0] || (env[1][0] == '~' && env))
	{
		cd_default(mini);
		if (env && env[1] && env[1][0])
		{
			if (env[1][0] == '~' && env[1][1] == '/' && env[1][2] && env)
				enter_dir(mini, env[1]);
		}
	}
	else if (chdir(env[1]) == -1)
	{
		er_cb(env[1], " : No such file or directory", 1, "cd : ");
		mini->exit = 1;
	}
	change_path(mini->env, oldenv);
	ft_bzero(oldenv, ft_strlen(oldenv));
}
