/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oltolmac <oltolmac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 16:07:58 by johuber           #+#    #+#             */
/*   Updated: 2025/06/08 18:05:48 by oltolmac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

int	error_msg(t_mini *mini, char *str)
{
	write(2, str, ft_strlen(str));
	mini->exit = 2;
	return (1);
}

void	er_cb(char *env, char *msg, int exit_code, char *com)
{
	if (exit_code == 1 && msg)
	{
		ft_putstr_fd(com, STDERR_FILENO);
		ft_putstr_fd(env, STDERR_FILENO);
		ft_putstr_fd(msg, STDERR_FILENO);
		write(STDERR_FILENO, "\n", 2);
	}
	else if (exit_code == 2)
	{
		printf("Error: Malloc error\n");
		exit(12);
	}
}

void	error_msg_b(t_mini *minsh, char *msg, int exit_code, char *com)
{
	if (exit_code == 1 && msg)
	{
		ft_putstr_fd(com, STDERR_FILENO);
		ft_putstr_fd(msg, STDERR_FILENO);
		write(STDERR_FILENO, "\n", 2);
		exit_code = 1;
	}
	else if (exit_code == 2)
	{
		printf("Error: Malloc error\n");
		free(minsh);
		exit(12);
	}
}
