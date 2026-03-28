/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oltolmac <oltolmac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 16:43:24 by jhuber            #+#    #+#             */
/*   Updated: 2025/06/13 17:32:47 by oltolmac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

char	*get_content(char *str)
{
	int		x;
	int		y;
	char	*content;

	x = 0;
	y = ft_strlen(str);
	while (str[x])
	{
		if (str[x] == '=')
			break ;
		x++;
	}
	content = (char *)malloc(sizeof(char) * (y - x + 1));
	if (!content)
		return (NULL);
	y = 0;
	x++;
	while (str[x])
	{
		content[y] = str[x];
		x++;
		y++;
	}
	content[y] = '\0';
	return (content);
}

int	check_equal_flag(char *str)
{
	int	x;
	int	check;

	x = 0;
	check = 0;
	while (str[x])
	{
		if (str[x] == '=')
		{
			check = 1;
			break ;
		}
		x++;
	}
	if (check)
	{
		if (str[x + 1] == '\0')
			return (0);
		return (1);
	}
	return (0);
}

char	*get_identificator(char *s, t_mini *mini, int check)
{
	int	x;

	if (ft_strcmp(s, "_") == 0)
		return (NULL);
	x = 0;
	if ((s[x] <= '9' && s[x] >= '0') || s[x] == '=' || s[x] == '$' || !s[x])
		check = 1;
	while (s[x] != '=' && s[x])
	{
		if (!((s[x] >= 'a' && s[x] <= 'z') || (s[x] >= '0' && s[x] <= '9')
				|| (s[x] >= 'A' && s[x] <= 'Z') || s[x] == '_'))
			check = 1;
		x++;
	}
	if (x != 0 && s[x - 1] == '$')
		check = 1;
	if (check)
	{
		error_msg_b(mini, "Not a valid Identifier", 1, "Export: ");
		mini->exit = 1;
		return (NULL);
	}
	if (!s[x])
		return (ft_strdup(s));
	return (ft_strndupe(mini, s, x));
}

void	make_new_node(char *str, t_mini *mini)
{
	t_env	*new_node;

	new_node = malloc(sizeof(t_env));
	new_node->name = get_identificator(str, mini, 0);
	if (new_node->name == NULL)
	{
		free(new_node);
		return ;
	}
	if (check_equal_flag(str))
	{
		new_node->value = get_content(str);
		if (!new_node->value)
		{
			free(new_node);
			return ;
		}
		new_node->equal_flag = 1;
	}
	else
	{
		new_node->value = ft_strdup(" ");
		new_node->equal_flag = 0;
	}
	ft_lstadd_front_b(&mini->env, new_node);
}

void	ft_export(t_mini *mini, char **input)
{
	int		x;

	x = 1;
	if (!input[1])
		export_empty(mini);
	else
	{
		while (input[x])
		{
			make_new_node(input[x], mini);
			x++;
		}
	}
}
