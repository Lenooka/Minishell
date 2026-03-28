/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_checks.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oltolmac <oltolmac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 13:30:33 by oltolmac          #+#    #+#             */
/*   Updated: 2025/06/23 15:17:37 by oltolmac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

char	*search_array(t_mini *mini, char **paths, char *name)
{
	int		i;
	char	*cmd;
	char	*tmp;

	i = 0;
	while (paths[i])
	{
		tmp = ft_strjoin(paths[i], "/");
		if (!tmp)
			free_exit_procces(mini, NULL);
		cmd = ft_strjoin(tmp, name);
		free(tmp);
		if (!cmd)
			free_exit_procces(mini, NULL);
		if (access(cmd, X_OK) == 0)
		{
			free_2d_array(paths);
			return (cmd);
		}
		free(cmd);
		i++;
	}
	free_2d_array(paths);
	return (NULL);
}

char	*find_path_dir(t_mini *mini, char *path_env, char *name)
{
	char	**paths;
	char	*cmd;

	paths = ft_split(path_env, ':');
	free(path_env);
	if (!paths)
		free_exit_procces(mini, NULL);
	cmd = search_array(mini, paths, name);
	return (cmd);
}

char	*find_path(t_mini *mini, char **envp)
{
	char	*path;
	int		i;

	i = 0;
	if (unset_path_check(mini) == 0)
		return (NULL);
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
		{
			path = ft_strdup(envp[i] + 5);
			if (!path)
				free_exit_procces(mini, NULL);
			return (path);
		}
		i++;
	}
	mini->exit = 1;
	return (NULL);
}

char	*get_relative_path(t_mini *mini, char *name)
{
	char	*path;
	char	*tmp;
	char	*cwd;

	cwd = getcwd(NULL, 0);
	if (!cwd)
	{
		ft_putstr_fd("Error: Getcwd fail\n", STDERR_FILENO);
		free_exit_procces(mini, NULL);
	}
	tmp = ft_strjoin(cwd, "/");
	free(cwd);
	if (!tmp)
		free_exit_procces(mini, NULL);
	path = ft_strjoin(tmp, name);
	free(tmp);
	if (!path)
		free_exit_procces(mini, NULL);
	return (path);
}

char	*path_extention(t_mini *mini, char *name)
{
	char	*path;

	if (ft_strncmp(name, "../", 3) == 0 || ft_strncmp(name, "./", 2) == 0)
		path = get_relative_path(mini, name);
	else if (name[0] == '/')
	{
		path = ft_strdup(name);
		if (!path)
			free_exit_procces(mini, NULL);
	}
	else
		return (NULL);
	return (path);
}
