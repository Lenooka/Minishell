/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_empty.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: johuber <johuber@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 18:51:25 by jhuber            #+#    #+#             */
/*   Updated: 2025/05/23 20:34:25 by johuber          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

void	get_smallest_biggest(t_env *envl, t_env **small, t_env **big)
{
	int	x;

	x = 0;
	*small = envl;
	*big = envl;
	envl = envl->next;
	while (envl)
	{
		x = ft_strncmp(envl->name, (*small)->name, \
			ft_strlen((*small)->name) + 1);
		if (x < 0)
			*small = envl;
		x = ft_strncmp(envl->name, (*big)->name, ft_strlen((*big)->name) + 1);
		if (x > 0)
			*big = envl;
		envl = envl->next;
	}
	if ((*small)->equal_flag)
		printf("%s %s=\"%s\"\n", "declare -x", \
			(char *)(*small)->name, (char *)(*small)->value);
	else
		printf("%s %s\"%s\"\n", "declare -x", \
			(char *)(*small)->name, (char *)(*small)->value);
}

void	print_smallest(t_env *lst, t_env **small, t_env *big)
{
	t_env	*tmp;

	tmp = lst;
	while (tmp)
	{
		if (ft_strncmp(tmp->name, (*small)->name, ft_strlen(tmp->name) + 1) > 0
			&& ft_strncmp(tmp->name, big->name, ft_strlen(tmp->name) + 1) < 0)
			big = tmp;
		tmp = tmp->next;
	}
	if (big->equal_flag)
		printf("%s %s=\"%s\"\n", "declare -x", \
			(char *)big->name, (char *)big->value);
	else
		printf("%s %s\"%s\"\n", "declare -x", \
			(char *)big->name, (char *)big->value);
	*small = big;
}

int	ft_lstsize_b(t_env *lst)
{
	int	count;

	count = 0;
	while (lst)
	{
		lst = lst->next;
		count++;
	}
	return (count);
}

void	export_empty(t_mini *mini)
{
	t_env	*small;
	t_env	*big;
	int		x;

	if (mini->env == NULL || (mini->env)->name == NULL)
		return ;
	get_smallest_biggest(mini->env, &small, &big);
	x = ft_lstsize_b(mini->env) - 2;
	while (x > 0)
	{
		print_smallest(mini->env, &small, big);
		x--;
	}
}
