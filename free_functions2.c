/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_functions2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oltolmac <oltolmac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 17:07:50 by johuber           #+#    #+#             */
/*   Updated: 2025/06/20 18:55:32 by oltolmac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

void	free_2d_array(char **str)
{
	int	x;

	x = 0;
	if (str == NULL)
		return ;
	while (str[x])
	{
		free(str[x]);
		x++;
	}
	free(str);
}

void	end_exit(t_mini *mini)
{
	mini->end = 0;
}

void	free_exit(void)
{
	exit (0);
}

void	ft_parser_exit(t_mini *mini, char **s0, char *s1, char *s2)
{
	if (s0 != NULL)
		free_2d_array(s0);
	if (s1 != NULL)
		free(s1);
	if (s2 != NULL)
		free(s2);
	if (mini->env)
		ft_free_env(mini->env);
	if (mini->cmd)
		ft_free_cmd(mini);
	rl_clear_history();
	close(mini->fd_in);
	close(mini->fd_out);
	exit(1);
}

void	ft_empty_pipe(t_mini *mini, t_cmd *tmp, char **s0, int error)
{
	if (error == 0)
		error_msg(mini, \
			"🪐 MiniSheLL 🪐: syntax error near unexpected token `|'\n");
	if (error == 1)
		error_msg(mini, "🪐 MiniSheLL 🪐 : Malloc failure in parsing\n");
	if (mini->cmd && !tmp)
		ft_free_cmd(mini);
	mini->cmd = tmp;
	if (tmp)
		ft_free_cmd(mini);
	if (s0)
		free_2d_array(s0);
}
