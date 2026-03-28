/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_vars.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: johuber <johuber@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 13:21:26 by oltolmac          #+#    #+#             */
/*   Updated: 2025/05/23 20:31:58 by johuber          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

char	*e_get_env_value(t_env *env, char *value)
{
	t_env	*tmp;

	tmp = env;
	while (tmp->next)
	{
		if (!ft_strcmp(tmp->name, value))
			return (tmp->value);
		tmp = tmp->next;
	}
	return (NULL);
}

int	is_there_q(char *str)
{
	int	i;
	int	d;
	int	s;

	i = 0;
	d = 0;
	s = 0;
	while (str[i])
	{
		if (is_dquote(str[i]))
			d++;
		if (is_squote(str[i]))
			s++;
		i++;
	}
	if (d != 0)
		return (1);
	if (s != 0)
		return (2);
	return (0);
}

char	*expand_var(t_mini *mini, char *str)
{
	char	*ret;
	char	*value;

	ret = NULL;
	if (is_there_q(str) == 1)
		str = ft_strtrim(str, "\"");
	else if (is_there_q(str) == 2)
	{
		str = ft_strtrim(str, "\'");
		return (str);
	}
	if (str[0] == '$' && str[1] != '?')
	{
		value = e_get_env_value(mini->env, str + 1);
		if (value)
			ret = ft_strdup(value);
	}
	else
		ret = ft_strdup(str);
	return (ret);
}
