/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: johuber <johuber@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 05:44:40 by jhuber            #+#    #+#             */
/*   Updated: 2025/05/25 18:35:34 by johuber          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

void	ft_pwd(void)
{
	int		x;
	char	env[4096 + 1];

	x = 0;
	if (getcwd(env, sizeof(env)) != NULL)
	{
		printf("%s\n", env);
		while (env[x])
		{
			env[x] = 0;
			x++;
		}
	}
	else
		perror("pwd:");
}
