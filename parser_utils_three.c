/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils_three.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: johuber <johuber@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 16:49:52 by johuber           #+#    #+#             */
/*   Updated: 2025/06/17 14:45:52 by johuber          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

int	skip_squote(char *str, int x, int *squote)
{
	x++;
	while (str[x])
	{
		if (is_squote(str[x]))
		{
			x++;
			*squote = *squote + 1;
			return (x);
		}
		x++;
	}
	return (x);
}

int	skip_dquote(char *str, int x, int *dquote)
{
	x++;
	while (str[x])
	{
		if (is_dquote(str[x]))
		{
			x++;
			*dquote = *dquote + 1;
			return (x);
		}
		x++;
	}
	return (x);
}

int	check_arrow_error(t_mini *mini, t_cmd *cmd, char *str)
{
	int	x;

	x = cmd->x;
	if (is_space(str[x]))
		x = skip_spaces(str, x);
	if (is_arrow(str[x]))
		return (error_msg(mini, \
				"syntax error near unexpected token `newline'\n"));
	if (!str[x])
		return (error_msg(mini, \
				"syntax error near unexpected token `newline'\n"));
	return (0);
}

char	*get_env_value(t_mini *m, t_env *env, char *v)
{
	t_env	*tmp;
	char	*str;

	tmp = env;
	if (v[0] == '?')
		return (free(v), handle_question(m));
	while (tmp->next)
	{
		if (!ft_strcmp(tmp->name, v))
		{
			str = ft_strdup(tmp->value);
			if (!str)
			{
				free(v);
				error_msg(m, "Malloc failure in tokenization\n");
				ft_parser_exit(m, m->msplit, m->cmd_line, m->free);
			}
			return (free(v), str);
		}
		tmp = tmp->next;
	}
	str = ft_strdup("");
	if (!str)
		return (free(v), ft_parser_exit(m, m->msplit, m->cmd_line, m->free), v);
	return (free(v), str);
}

char	*get_env_name(t_mini *mini, char *str, int x)
{
	int		start;
	char	*name;

	start = ++x;
	if (str[x] == '$')
	{
		name = ft_strdup("$");
		if (!name)
		{
			error_msg(mini, "🪐 MiniSheLL 🪐 : Malloc failure in tokenization\n");
			ft_parser_exit(mini, mini->msplit, mini->cmd_line, mini->free);
		}
		return (name);
	}
	if (str[x] == '?')
		x++;
	else
	{
		while (is_valid_expansion(str[x]))
			x++;
	}
	return (ft_strndup(mini, str + start, x - start, 1));
}
