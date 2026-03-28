/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oltolmac <oltolmac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 04:45:13 by jhuber            #+#    #+#             */
/*   Updated: 2025/06/17 20:12:58 by oltolmac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

int	exit_error_b(t_mini *mini, int x)
{
	if (x == 1)
	{
		mini->tom_exit = 1;
		error_msg_b(mini, "too many arguments", 1, "exit : ");
	}
	if (x == 2)
	{
		error_msg_b(mini, " : numeric argument required", 1, "exit");
	}
	return (x);
}

int	exit_num(int number)
{
	if (number >= 0 && number <= 255)
		return (number);
	if (number > 255)
		return (exit_num(number - 256));
	if (number < 0)
		return (exit_num(number + 256));
	return (number);
}

int	prep_atoi(char *str)
{
	int	x;

	x = 0;
	if (str[x] == '-' || str[x] == '+')
		x++;
	if (str[x] == '\0')
		return (0);
	while (str[x])
	{
		if (str[x] > '9' || str[x] < '0')
			return (0);
		x++;
	}
	return (1);
}

long	ft_strtol(const char *str, char **endptr)
{
	long	result;

	result = 0;
	while (*str == ' ' || (*str >= '\t' && *str <= '\r'))
		str++;
	if (*str == '-' || *str == '+')
		str++;
	while (*str >= '0' && *str <= '9')
	{
		if (result > (LONG_MAX - (*str - '0')) / 10)
		{
			if (endptr != NULL)
			{
				*endptr = (char *)str;
			}
			return (LONG_MAX);
		}
		result = result * 10 + (*str - '0');
		str++;
	}
	if (endptr != NULL)
	{
		*endptr = (char *)str;
	}
	return (result);
}

void	ft_exit(t_mini *mini, char **input)
{
	long	number;

	number = 0;
	mini->tom_exit = 0;
	if (mini->cmd_am <= 1)
		printf("exit\n");
	number = exit_check_arg(mini, number, input);
	number = exit_num(number);
	mini->exit = number;
	if (mini->tom_exit == 1)
		return ;
	free_exit_procces(mini, NULL);
}
