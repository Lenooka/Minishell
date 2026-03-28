/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils_two.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: johuber <johuber@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 15:36:03 by johuber           #+#    #+#             */
/*   Updated: 2025/06/13 17:14:03 by johuber          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

char	*ft_strndup(t_mini *mini, char *s, size_t n, int free)
{
	char			*dest;
	unsigned int	i;

	i = 0;
	dest = (char *)malloc(sizeof(char) * (n + 1));
	if (!dest)
	{
		error_msg(mini, "🪐 MiniSheLL 🪐 : Malloc failure in strndup\n");
		if (free)
			ft_parser_exit(mini, mini->msplit, mini->cmd_line, mini->free);
		return (NULL);
	}
	while ((s[i] != '\0') && (i < n))
	{
		dest[i] = s[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

int	is_arrow(char c)
{
	if (c == '>' || c == '<')
		return (1);
	return (0);
}

t_cmd	*get_last_node(t_cmd *cmd)
{
	if (cmd == NULL)
		return (cmd);
	while (cmd->next != NULL)
		cmd = cmd->next;
	return (cmd);
}

char	*p_ft_strjoin(t_mini *mini, char *s1, char *s2)
{
	size_t	olen;
	size_t	tlen;
	char	*join;

	if (s2 == NULL)
	{
		error_msg(mini, "🪐 MiniSheLL 🪐 : Malloc failure in tokenization\n");
		ft_parser_exit(mini, mini->msplit, mini->cmd_line, s1);
	}
	olen = ft_strlen(s1);
	tlen = ft_strlen(s2);
	join = (char *)malloc(sizeof(char) * (olen + tlen + 1));
	if (!join)
	{
		error_msg(mini, "🪐 MiniSheLL 🪐 : Malloc failure in tokenization\n");
		free(s2);
		ft_parser_exit(mini, mini->msplit, mini->cmd_line, s1);
	}
	ft_strlcpy(join, s1, olen + 1);
	ft_strlcpy(join + olen, s2, tlen + 1);
	free(s1);
	free(s2);
	return (join);
}

void	skip_expansion(t_cmd *cmd, char *str)
{
	cmd->x++;
	if (str[cmd->x] == '$')
	{
		cmd->x++;
		return ;
	}
	if (str[cmd->x] == '?')
	{
		cmd->x++;
		return ;
	}
	while (is_valid_expansion(str[cmd->x]))
		cmd->x++;
}
