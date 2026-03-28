/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oltolmac <oltolmac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 20:56:38 by oltolmac          #+#    #+#             */
/*   Updated: 2025/06/17 20:54:44 by oltolmac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

int	number_exit(t_mini *mini, char **input)
{
	long	number;
	char	*end;

	number = ft_strtol(input[1], &end);
	if (number > INT_MAX || number < INT_MIN)
	{
		mini->exit = 2;
		free_exit_procces(mini, "exit : numeric argument required\n");
	}
	number = ft_atoi(input[1]);
	return (number);
}

int	exit_check_arg(t_mini *mini, int number, char **input)
{
	if (!input[1])
	{
		if (mini->exit == 130)
			free_exit_procces(mini, NULL);
	}
	else if (input[1] && !input[2])
	{
		if (prep_atoi(input[1]))
			number = number_exit(mini, input);
		else
			number = exit_error_b(mini, 2);
	}
	else
	{
		if (!prep_atoi(input[1]))
			number = exit_error_b(mini, 2);
		else
			number = exit_error_b(mini, 1);
	}
	return (number);
}
