/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oltolmac <oltolmac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 15:43:04 by oltolmac          #+#    #+#             */
/*   Updated: 2025/06/23 14:58:44 by oltolmac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

char	*h_quote_parsing(t_mini *mini, char *tmp, int *start, int *x)
{
	char	*str;

	str = mini->free;
	mini->free = NULL;
	if ((*start) != (*x))
	{
		if (!tmp)
			tmp = ft_strndup(mini, str + (*start), (*x) - (*start), 1);
		else
			tmp = p_ft_strjoin(mini, tmp,
					ft_strndup(mini, str + (*start), (*x) - (*start), 0));
	}
	(*start) = (*x) + 1;
	*x = h_skip_quote(str, *x);
	if (!tmp)
		tmp = ft_strndup(mini, str + (*start), (*x) - (*start), 1);
	else
		tmp = p_ft_strjoin(mini, tmp,
				ft_strndup(mini, str + (*start), (*x) - (*start), 0));
	(*x)++;
	(*start) = (*x);
	return (tmp);
}

char	*h_parse_ident(t_mini *m, char *s)
{
	int		x;
	int		start;
	char	*t;

	x = 0;
	start = 0;
	t = NULL;
	while (s[x])
	{
		m->free = s;
		if (is_quote(s[x]))
			t = h_quote_parsing(m, t, &start, &x);
		else
			x++;
	}
	m->free = NULL;
	if (start != x)
	{
		if (!t)
			t = ft_strndup(m, s + start, x - start, 1);
		else
			t = p_ft_strjoin(m, t, ft_strndup(m, s + start, x - start, 0));
	}
	free(s);
	return (t);
}

void	heredoc_child(int fd, char *delimiter, t_mini *mini)
{
	char	*line;

	delimiter = parse_and_quote(mini, delimiter);
	signal(SIGINT, heredoc_signal_handle);
	while (1)
	{
		disable_quit_signals();
		line = readline("> ");
		if (g_global == SIGINT)
			sigint_exithere(mini, line, delimiter);
		if (!line && g_global != SIGINT)
			heredoc_warn(mini, delimiter, line);
		if (line && ft_strcmp(line, delimiter) == 0)
		{
			free(line);
			break ;
		}
		if (line && mini->quote == 0)
			line = here_expansion(mini, line, 0, 0);
		ft_putendl_fd(line, fd);
		free(line);
	}
	close(fd);
	free_exit_heredoc(mini, NULL, delimiter);
}

int	heredoc_handle(t_mini *mini, char *delimiter, int index)
{
	pid_t	pid;
	int		status;

	if (!delimiter)
		free_exit_procces(mini, "malloc fail!");
	if (mini->heredoc_buf)
		free(mini->heredoc_buf);
	mini->heredoc_buf = temp_file(index, mini);
	if (!mini->heredoc_buf)
		return (free(delimiter), g_global = 130, 0);
	mini->here_fd = open(mini->heredoc_buf, O_CREAT | O_WRONLY | O_TRUNC, 0600);
	if (mini->here_fd < 0)
		return (free(mini->heredoc_buf),
			mini->heredoc_buf = NULL, free(delimiter), g_global = 130, 0);
	pid = fork();
	if (pid < 0)
		return (free(delimiter), close(mini->here_fd), g_global = 130, 0);
	if (pid == 0)
		heredoc_child(mini->here_fd, delimiter, mini);
	close(mini->here_fd);
	waitpid(pid, &status, 0);
	if (WIFEXITED(status) && WEXITSTATUS(status) == 0)
		return (free(delimiter), 0);
	free(delimiter);
	return (1);
}

int	heredoc_check(t_mini *m, t_cmd *list)
{
	if (check_redir_flag(list) == 0)
		return (0);
	while (list)
	{
		m->i = 0;
		while (list->cmd_w_flags && list->cmd_w_flags[m->i])
		{
			if (ft_strcmp(list->cmd_w_flags[m->i], "<<") == 0
				&& list->cmd_w_flags[m->i + 1])
			{
				heredoc_handle(m, ft_strdup(list->cmd_w_flags[m->i + 1]), m->i);
				if (g_global == 130)
					return (ft_free_cmd(m), 1);
				if (!m->heredoc_buf)
					free_exit_heredoc(m, "Heredoc fail", NULL);
				free(list->cmd_w_flags[m->i + 1]);
				list->cmd_w_flags[m->i + 1] = ft_strdup(m->heredoc_buf);
				if (!list->cmd_w_flags[m->i + 1])
					return (ft_free_cmd(m), 1);
			}
			m->i++;
		}
		list = list->next;
	}
	return (m->heredoc_flag = 1, 0);
}
