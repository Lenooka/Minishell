/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oltolmac <oltolmac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 16:14:17 by jhuber            #+#    #+#             */
/*   Updated: 2025/06/23 14:51:13 by oltolmac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

int	unset_path_check(t_mini *mini)
{
	t_env	*lst;

	lst = mini->env;
	while (lst->next)
	{
		if (ft_strncmp(lst->name, "PATH", 5) == 0)
		{
			if (lst->value && lst->value[0] != '\0')
				return (1);
		}
		lst = lst->next;
	}
	return (0);
}

void	rm_first(t_env **env)
{
	t_env	*tmp;

	tmp = *env;
	(*env) = (*env)->next;
	free(tmp->name);
	free(tmp->value);
	free(tmp);
}

void	rm_nodes(t_env **env, char *str)
{
	t_env	*tmp;
	t_env	*lst;

	lst = *env;
	tmp = lst;
	if (!lst)
		return ;
	while (lst->next)
	{
		if (ft_strcmp((char *)(tmp)->name, str) == 0)
		{
			rm_first(env);
			break ;
		}
		else if (ft_strcmp((char *)(lst)->next->name, str) == 0)
		{
			tmp = lst->next;
			lst->next = lst->next->next;
			free(tmp->name);
			free(tmp->value);
			free(tmp);
			break ;
		}
		lst = lst->next;
	}
}

int	valid_ident(char *str)
{
	int	x;
	int	flag;

	if (ft_strcmp(str, "_") == 0)
		return (2);
	if ((str[0] >= '0' && str[0] <= '9') || str[0] == '=')
		return (0);
	x = 0;
	flag = 0;
	while (str[x])
	{
		if ((str[x] >= 'a' && str[x] <= 'z') || (str[x] >= '0' && str[x] <= '9')
			|| (str[x] >= 'A' && str[x] <= 'Z') || str[x] == '_')
			flag = 1;
		else
			return (0);
		x++;
	}
	if (flag == 1)
		return (1);
	return (0);
}

void	ft_unset(t_mini *mini, char **input)
{
	int	x;
	int	option;

	x = 1;
	if (!input[x])
		return ;
	while (input[x])
	{
		option = valid_ident(input[x]);
		if (option == 2)
			x++;
		if (option == 0)
			break ;
		rm_nodes(&mini->env, input[x]);
		x++;
	}
}
