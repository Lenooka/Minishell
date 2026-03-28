/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olena <olena@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 03:35:28 by jhuber            #+#    #+#             */
/*   Updated: 2025/06/05 01:58:10 by olena            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

void	ft_env(t_mini *mini)
{
	t_env	*tmp;

	if (!mini->env)
	{
		error_msg_b(mini, "environment variable list not set", 1, "env");
		return ;
	}
	tmp = mini->env;
	if (!tmp)
		return ;
	while (tmp)
	{
		printf("%s=%s\n", (tmp)->name, (tmp)->value);
		tmp = (tmp)->next;
	}
	return ;
}
