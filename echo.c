/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: johuber <johuber@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 21:35:11 by jhuber            #+#    #+#             */
/*   Updated: 2025/05/23 19:02:40 by johuber          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

void	no_flag(char **input)
{
	int		x;

	x = 1;
	while (input[x])
	{
		ft_putstr_fd(input[x], STDOUT_FILENO);
		if (input[x + 1])
			ft_putstr_fd(" ", STDOUT_FILENO);
		x++;
	}
	write(1, "\n", 1);
}

void	echo_flag(char **input, int x)
{
	while (input[x])
	{
		ft_putstr_fd(input[x], STDOUT_FILENO);
		x++;
		if (input[x])
			ft_putstr_fd(" ", STDOUT_FILENO);
	}
}

int	check_flag(char *input)
{
	int	x;

	x = 0;
	if (!input)
		return (0);
	if (ft_strlen(input) < 2)
		return (0);
	if (input[x] == '-' && input[x + 1] == 'n')
	{
		x++;
		while (input[x])
		{
			if (input[x] != 'n')
				return (0);
			x++;
		}
		return (1);
	}
	return (0);
}

void	ft_echo(char **inputs)
{
	int	x;
	int	option;

	x = 1;
	option = 0;
	if (inputs[x] == NULL)
	{
		write(1, "\n", 1);
		return ;
	}
	option = check_flag(inputs[x]);
	x = option;
	while (check_flag(inputs[x]))
		x++;
	if (option)
	{
		echo_flag(inputs, x);
		return ;
	}
	no_flag(inputs);
	return ;
}
