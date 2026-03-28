/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils_six.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oltolmac <oltolmac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 15:42:44 by oltolmac          #+#    #+#             */
/*   Updated: 2025/06/22 15:45:32 by oltolmac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

void	dol_expansion(t_mini *mini, t_cmd *cmd, char *str)
{
	char	*tmp;

	if (!is_valid_expansion(str[cmd->x + 1]) && str[cmd->x + 1] != '?')
		tmp = dol_empty_expansion(mini, cmd, str);
	else
	{
		tmp = get_env_value(mini, mini->env, get_env_name(mini, str, cmd->x));
		skip_expansion(cmd, str);
		if (tmp[0] && has_space(tmp))
		{
			parse_exp(mini, cmd, str, tmp);
			return ;
		}
	}
	if (!tmp[0])
		cmd->empty[cmd->y] = 1;
	if (str[cmd->x] == '$' || is_no_tokens(str[cmd->x]) \
		|| is_quote(str[cmd->x]))
		handle_token_merge(mini, cmd, str, tmp);
	else
		cmd->cmd_w_flags[cmd->y++] = tmp;
}

int	check_redir_flag(t_cmd *list)
{
	int	i;

	i = 0;
	while (list)
	{
		i += list->redir;
		list = list->next;
	}
	return (i);
}

char	*parse_and_quote(t_mini *mini, char *delimiter)
{
	mini->quote = has_quotes(delimiter);
	if (mini->quote)
		delimiter = h_parse_ident(mini, delimiter);
	return (delimiter);
}

int	calc_skip_exp(char *str, int y)
{
	y++;
	if (str[y] == '?')
		y++;
	else
	{
		while (is_valid_expansion(str[y]) && str[y])
			y++;
	}
	return (y);
}

int	calc_exp_parsing(t_mini *mini, char *str, int y, int *count)
{
	int		x;
	char	*env;

	env = get_env_value(mini, mini->env, get_env_name(mini, str, y));
	y = calc_skip_exp(str, y);
	if (env[0] == '\0' || !has_space(env))
		return ((*count)++, free(env), y);
	x = skip_spaces(env, 0);
	if (!env[x])
		return ((*count)++, free(env), skip_token_merge(mini, str, y, count));
	while (env[x])
	{
		if (!is_space(env[x]))
		{
			(*count)++;
			while (!is_space(env[x]) && env[x])
				x++;
		}
		else
			x++;
	}
	if (!is_space(env[x - 1]))
		y = skip_token_merge(mini, str, y, count);
	return (free(env), y);
}
