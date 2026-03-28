/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_pars_u.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oltolmac <oltolmac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 15:44:26 by oltolmac          #+#    #+#             */
/*   Updated: 2025/06/22 19:06:31 by oltolmac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

char	*temp_file(int index, t_mini *mini)
{
	char	*tmp;
	int		i;

	tmp = NULL;
	g_global = 0;
	mini->heredoc_buf = ft_strdup("/tmp/minishell_heredoc");
	if (!mini->heredoc_buf)
		return (NULL);
	i = 0;
	while (i < index)
	{
		tmp = ft_strdup(mini->heredoc_buf);
		free(mini->heredoc_buf);
		if (!tmp)
			return (NULL);
		mini->heredoc_buf = ft_strjoin(tmp, "e");
		free(tmp);
		if (!mini->heredoc_buf)
			return (NULL);
		i++;
	}
	return (mini->heredoc_buf);
}

int	check_q_exp(t_mini *mini, char *line)
{
	int		i;
	char	**tok;
	int		j;

	i = 0;
	if (ft_strchr(line, '$') == NULL)
		i++;
	tok = ft_split(mini->cmd_line, '<');
	if (!tok)
		free_exit_heredoc(mini, "Malloc Fail in heredoc", line);
	j = 0;
	while (tok[j])
		j++;
	if (ft_strchr(tok[j - 1], '"') != NULL)
		i++;
	if (ft_strchr(tok[j - 1], '\'') != NULL)
		i++;
	free_2d_array(tok);
	return (i);
}

int	has_quotes(char *str)
{
	int	x;

	x = 0;
	while (str[x])
	{
		if (is_quote(str[x]))
			return (1);
		x++;
	}
	return (0);
}

int	h_skip_quote(char *str, int x)
{
	if (is_dquote(str[x]))
	{
		x++;
		while (!is_dquote(str[x]))
			x++;
	}
	else if (is_squote(str[x]))
	{
		x++;
		while (!is_squote(str[x]))
			x++;
	}
	return (x);
}
