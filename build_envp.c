/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_envp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oltolmac <oltolmac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 21:11:12 by oltolmac          #+#    #+#             */
/*   Updated: 2025/06/20 16:52:34 by oltolmac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

void	sigint_exithere(t_mini *mini, char *line, char *del)
{
	mini->exit = 128 + SIGINT;
	free_exit_heredoc(mini, line, del);
	(void)mini;
	(void)line;
}

int	count_env(t_env *env)
{
	int	count;

	count = 0;
	while (env)
	{
		if (env->equal_flag)
			count++;
		env = env->next;
	}
	return (count);
}

void	fill_envp(t_mini *mini, char **envp, t_env *env)
{
	int		i;
	char	*tmp;

	i = 0;
	while (env)
	{
		if (env->equal_flag)
		{
			tmp = ft_strjoin(env->name, "=");
			if (!tmp)
				free_exit_procces(mini, NULL);
			envp[i] = ft_strjoin(tmp, env->value);
			free(tmp);
			if (!envp[i])
				free_exit_procces(mini, NULL);
			i++;
		}
		env = env->next;
	}
	envp[i] = NULL;
}

char	**build_envp(t_mini *mini, t_env *env)
{
	int		count;
	char	**envp;

	count = count_env(env);
	envp = malloc(sizeof(char *) * (count + 1));
	if (!envp)
		return (NULL);
	fill_envp(mini, envp, env);
	return (envp);
}
