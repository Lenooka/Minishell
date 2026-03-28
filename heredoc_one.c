/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_one.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oltolmac <oltolmac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/08 17:51:12 by oltolmac          #+#    #+#             */
/*   Updated: 2025/06/11 21:01:53 by oltolmac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

void	disable_quit_signals(void)
{
	struct termios	term;

	tcgetattr(STDIN_FILENO, &term);
	term.c_cc[VQUIT] = _POSIX_VDISABLE;
	tcsetattr(STDIN_FILENO, TCSANOW, &term);
}

void	split_exit_free(int o, t_mini *mini, char *str, char **res)
{
	if (o == 1)
		free_exit_heredoc(mini, "Malloc failure in heredoc\n", str);
	if (o == 2)
	{
		free_arr_back(res, mini->hp);
		free_exit_heredoc(mini, "Malloc failure in heredoc\n", str);
	}
}

char	*ft_herestrndup(t_mini *mini, char *s, size_t n, char **r)
{
	char			*dest;
	unsigned int	i;

	i = 0;
	dest = (char *)malloc(sizeof(char) * (n + 1));
	if (!dest)
		split_exit_free(2, mini, s, r);
	while ((s[i] != '\0') && (i < n))
	{
		dest[i] = s[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

char	**split_keep_sep(t_mini *m, char *str, char sep)
{
	int		i;
	int		count;
	int		start;
	char	**result;

	i = 0;
	count = count_split(str, sep);
	start = 0;
	m->hp = 0;
	result = malloc(sizeof(char *) * (count + 1));
	if (!result)
		split_exit_free(1, m, str, result);
	while (str[i])
	{
		if (str[i] == sep && i != 0)
		{
			result[m->hp++] = ft_herestrndup(m, str + start, i - start, result);
			start = i;
		}
		i++;
	}
	if (i > start)
		result[m->hp++] = ft_herestrndup(m, str + start, i - start, result);
	result[m->hp++] = NULL;
	return (result);
}

int	count_dollar(char *str)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] == '$')
			count++;
		i++;
	}
	return (count);
}
