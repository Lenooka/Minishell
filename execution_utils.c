/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oltolmac <oltolmac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 19:09:20 by johuber           #+#    #+#             */
/*   Updated: 2025/06/22 14:49:04 by oltolmac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

int	ft_lstsizexec(t_cmd *lst)
{
	int	count;

	count = 0;
	while (lst)
	{
		lst = lst->next;
		count++;
	}
	return (count);
}

char	**clean_cmd(char **cmd, int heredoc_flag, t_mini *mini)
{
	char	**clean;
	int		i;
	int		count;

	i = 0;
	count = 0;
	replace_cmd(cmd, heredoc_flag, mini, i);
	while (cmd[i])
	{
		if (ft_strcmp(cmd[i], "<") == 0 || ft_strcmp(cmd[i], ">") == 0
			|| ft_strcmp(cmd[i], ">>") == 0 || ft_strcmp(cmd[i], "<<") == 0)
			i += 2;
		else
		{
			count++;
			i++;
		}
	}
	clean = fill_clean(cmd, count);
	free_2d_array(cmd);
	return (clean);
}

char	**fill_clean(char **cmd, int count)
{
	char	**clean;
	int		i;
	int		j;

	i = 0;
	j = 0;
	clean = malloc(sizeof(char *) * (count + 1));
	if (!clean)
		return (NULL);
	while (cmd[i])
	{
		if (ft_strcmp(cmd[i], "<") == 0 || ft_strcmp(cmd[i], ">") == 0
			|| ft_strcmp(cmd[i], ">>") == 0 || ft_strcmp(cmd[i], "<<") == 0)
			i += 2;
		else
		{
			clean[j] = remove_quotes(cmd[i]);
			if (!clean[j])
				clean[j] = ft_strdup(cmd[i]);
			j++;
			i++;
		}
	}
	clean[j] = NULL;
	return (clean);
}

void	remove_quotes_from_array(char **arr)
{
	int		i;
	char	*tmp;

	if (!arr)
		return ;
	i = 0;
	while (arr[i])
	{
		tmp = remove_quotes(arr[i]);
		if (tmp)
		{
			free(arr[i]);
			arr[i] = tmp;
		}
		i++;
	}
}

char	*remove_quotes(char *str)
{
	int		i;
	int		j;
	char	*new;
	char	quote;

	i = 0;
	j = 0;
	quote = 0;
	if (!str)
		return (NULL);
	new = malloc(sizeof(char) * (ft_strlen(str) + 1));
	if (!new)
		return (NULL);
	while (str[i])
	{
		if ((str[i] == '\'' || str[i] == '\"') && quote == 0)
			quote = str[i];
		else if (str[i] == quote)
			quote = 0;
		else
			new[j++] = str[i];
		i++;
	}
	new[j] = '\0';
	return (new);
}
