/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oltolmac <oltolmac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 13:41:28 by oltolmac          #+#    #+#             */
/*   Updated: 2025/06/11 18:02:14 by oltolmac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

char	*e_get_env_name(char *env)
{
	char	*name;
	int		i;

	i = 0;
	while (env[i] && env[i] != '=')
		i++;
	name = (char *)malloc(sizeof(char) * (i + 1));
	if (!name)
		return (NULL);
	i = 0;
	while (env[i] && env[i] != '=')
	{
		name[i] = env[i];
		i++;
	}
	name[i] = '\0';
	return (name);
}

t_env	*set_flags(t_mini *mini, char **env, t_env *env_list)
{
	env_list->equal_flag = (ft_strchr(env[mini->i], '=') != NULL);
	return (env_list);
}

char	*envl_content_fill(const char *str, int c)
{
	int		i;
	char	*result;
	int		x;
	int		len;

	i = 0;
	x = 0;
	len = 0;
	while (str[i] != '\0' && str[i] != (char)c)
		i++;
	i++;
	if (str[i] == '\0' || str[i + 1] == '\0')
		return (ft_strdup("  "));
	len = ft_strlen(str) - i;
	result = (char *)malloc(sizeof(char) * (len + 1));
	if (!result)
		return (NULL);
	while (str[i] != '\0')
	{
		result[x] = str[i];
		x++;
		i++;
	}
	result[x] = '\0';
	return (result);
}

t_env	*init_env_node(t_mini *mini, char **env)
{
	t_env	*node;

	node = malloc(sizeof(t_env));
	if (!node)
		return (NULL);
	node->name = e_get_env_name(env[mini->i]);
	if (!node->name)
		return (free(node), NULL);
	node->value = ft_strdup(ft_strchr(env[mini->i], '=') + 1);
	if (!node->value)
		return (free(node->name), free(node), NULL);
	set_flags(mini, env, node);
	node->next = NULL;
	return (node);
}

t_env	*def_env(t_mini *mini, char **env)
{
	t_env	*head;
	t_env	*current;
	t_env	*new_node;

	head = init_env_node(mini, env);
	if (!head)
	{
		ft_putstr_fd("Enviroment variables list malloc error!", STDERR_FILENO);
		exit(1);
	}
	current = head;
	mini->i++;
	while (mini->i < mini->size)
	{
		new_node = init_env_node(mini, env);
		if (!new_node)
			return (NULL);
		current->next = new_node;
		current = new_node;
		mini->i++;
	}
	return (head);
}
