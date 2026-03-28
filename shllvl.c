/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shllvl.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oltolmac <oltolmac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 20:58:12 by oltolmac          #+#    #+#             */
/*   Updated: 2025/06/20 19:49:08 by oltolmac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

void	add_shlvl_one(t_mini *mini)
{
	t_env	*new_node;

	new_node = malloc(sizeof(t_env));
	if (!new_node)
		return ;
	new_node->name = ft_strdup("SHLVL");
	new_node->value = ft_strdup("1");
	if (!new_node->name || !new_node->value)
	{
		free(new_node->name);
		free(new_node->value);
		free(new_node);
		return ;
	}
	new_node->equal_flag = 1;
	new_node->next = mini->env;
	mini->env = new_node;
}

void	adjust_shlvl(t_mini *mini)
{
	t_env	*node;
	int		level;

	node = mini->env;
	mini->shlvl = 1;
	while (node)
	{
		if (ft_strcmp(node->name, "SHLVL") == 0)
		{
			level = ft_atoi(node->value);
			if (level < 0)
				level = 0;
			level += 1;
			free(node->value);
			node->value = ft_itoa(level);
			return ;
		}
		node = node->next;
	}
	add_shlvl_one(mini);
}

void	decrs_shlvl(t_mini *mini)
{
	t_env	*node;
	int		level;

	node = mini->env;
	while (node)
	{
		if (ft_strcmp(node->name, "SHLVL") == 0)
		{
			level = ft_atoi(node->value);
			if (level < 0)
				level = 0;
			level--;
			free(node->value);
			node->value = ft_itoa(level);
			return ;
		}
		node = node->next;
	}
}

void	env_define(t_mini *mini, char **envp)
{
	mini->skip = 0;
	mini->env = def_env(mini, envp);
	if (!mini->env)
	{
		ft_putstr_fd("Enviroment vars malloc fail!\n", STDERR_FILENO);
		exit(1);
	}
	mini->benv = NULL;
	mini->shlvl = 0;
}
