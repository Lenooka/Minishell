/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_minishell.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oltolmac <oltolmac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 14:48:00 by oltolmac          #+#    #+#             */
/*   Updated: 2025/06/23 15:12:12 by oltolmac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_MINISHELL_H
# define FT_MINISHELL_H

# include "libft/libft.h"
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <string.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <limits.h> 
# include <signal.h>
# include <sys/wait.h>
# include <errno.h>
# include <sys/stat.h>
# include <stddef.h>
# include <sys/ioctl.h>
# include <termios.h>
# include <term.h>
# include <curses.h>

extern int			g_global;
typedef struct s_env
{
	char			*name;
	char			*value;
	int				equal_flag;
	struct s_env	*next;
}	t_env;

typedef struct s_cmd
{
	char			*name;
	char			*path;
	char			*free;
	char			**cmd_w_flags;
	char			**cmd_no_redir;
	int				*empty;
	int				redir;
	int				x;
	int				y;
	struct s_cmd	*next;
}	t_cmd;

typedef struct s_mini
{
	char			**msplit;
	int				end;
	int				fd;
	struct s_env	*env;
	struct s_cmd	*cmd;
	char			*cmd_line;
	char			*free;
	int				cmd_am;
	int				i;
	int				size;
	int				exit;
	int				b_ex;
	int				fd_in;
	int				fd_out;
	int				pipefd[2];
	char			*heredoc_buf;
	int				here_fd;
	int				hp;
	int				heredoc_flag;
	int				f;
	int				tom_exit;
	char			**sp;
	int				q_h;
	char			**benv;
	int				shlvl;
	int				h;
	int				l;
	int				ret;
	int				skip;
	int				quote;
}	t_mini;

void				end_exit(t_mini *mini);

//ENV_LIST
t_env				*def_env(t_mini *mini, char **env);
void				decrs_shlvl(t_mini *mini);
void				add_shlvl_one(t_mini *mini);
void				adjust_shlvl(t_mini *mini);
void				decrs_shlvl(t_mini *mini);
char				**build_envp(t_mini *mini, t_env *env);
void				env_define(t_mini *mini, char **envp);
void				print2d(char **ar_cm);

//PARSER
int					wrong_parsing(t_mini *mini, char *command);
int					multiple_parsing_prep(char **str, t_mini *mini);
int					multiple_parsing(t_mini *mini, char *str, t_cmd *cmd);
void				dol_expansion(t_mini *mini, t_cmd *cmd, char *str);
int					single_parsing_prep(char *str, t_mini *mini);
int					single_parsing(t_mini *mini, char *str, t_cmd *cmd);
int					parse_arrow(t_mini *mini, t_cmd *cmd, char *str);
void				parse_char(t_mini *mini, t_cmd *cmd, char *str);
void				parse_exp(t_mini *mini, t_cmd *cmd, char *str0, char *str);

//PARSER UTILS
int					is_space(char c);
int					is_no_tokens(char c);
int					skip_spaces(char *str, int x);
int					rev_skip_spaces(char *str, int x);
int					skip_quotes(char *str, int x);
int					quote_check(char *str, int squotes, int dquotes);
char				**calc_tokens(t_mini *mini, char *str, t_cmd *cmd);
char				*ft_strndupe(t_mini *mnshll, char *s, int n);
char				*ft_strndup(t_mini *mini, char *s, size_t n, int free);
int					is_arrow(char c);
int					calc_quote(t_mini *mini, char *str, int x, int *count);
int					calc_dollar(t_mini *mini, char *str, int x, int *count);
int					calc_arrow(char *str, int x, int *count);
int					calc_char(t_mini *mini, char *str, int x, int *count);
t_cmd				*get_last_node(t_cmd *cmd);
char				*p_ft_strjoin(t_mini *mini, char *s1, char *s2);
void				go_inquote(t_mini *mini, t_cmd *cmd, char *str);
void				handle_squote(t_mini *mini, t_cmd *cmd,	\
					char *str, int start);
void				skip_expansion(t_cmd *cmd, char *str);
char				*get_env_value(t_mini *mini, t_env *env, char *value);
char				*get_env_name(t_mini *mini, char *str, int x);
t_cmd				*make_cmd_list(t_mini *mini, int x);
int					skip_dquote(char *str, int x, int *dquote);
int					skip_squote(char *str, int x, int *squote);
int					check_arrow_error(t_mini *mini, t_cmd *cmd, char *str);
int					get_token_no_token_size(char **str);
void				make_cmd_no_redir(t_mini *mini, t_cmd *cmd);
void				set_tokens(t_mini *mini, t_cmd *cmd);
char				*handle_question(t_mini *mini);
int					quotes_msg(t_mini *mini, int quotes);
void				handle_squote_merge(t_mini *mini, t_cmd *cmd, \
					char *str, char *res);
void				only_expansion(t_mini *mini, char *str, \
					char **tmp, int *start);
void				char_expansion(t_mini *mini, char *str, \
					char **tmp, int *start);
char				*handle_empty_dquote(t_mini *mini, t_cmd *cmd);
char				*handle_token_merge(t_mini *mini, \
					t_cmd *cmd, char *str, char *res);
int					calc_merge_quote(char *str, int x);
char				*dol_empty_expansion(t_mini *mini, t_cmd *cmd, char *str);
int					is_valid_expansion(char c);
int					calc_exp_parsing(t_mini *mini, char *str, int x, \
					int *count);
int					has_space(char *str);
int					skip_token_merge(t_mini *mini, char *s, int x, int *count);
char				*parse_exp_merge(t_mini *mini, t_cmd *cmd, char *res, \
					char *str);
char				*parse_and_quote(t_mini *mini, char *delimiter);
char				*parse_exp_tmp(t_mini *mini, t_cmd *cmd, char *tmp, int *x);
void				parse_exp_deallocat(t_mini *mini, t_cmd *cmd);
void				parse_exp_allocat(t_mini *mini, t_cmd *cmd, char *str, \
					char *res);
char				*m_handle_space_only(t_mini *mini, char *res);
//Custom Split
char				**ft_msplit(char *s, char c);
int					ft_slcheck_quotes(char *str, int len);
int					ft_dlcheck_quotes(char *str, int len);
void				ft_split_continue(char **str, int *x);
char				*c_ft_strndup(char *s, size_t n);

//CHARACTER CHECKS
int					is_pipe(char *str);
int					is_quote(char c);
int					is_squote(char c);
int					is_dquote(char c);

//ERROR HANDLING
int					error_msg(t_mini *mini, char *str);
void				dup_error(t_mini *mini);
void				open_error(t_mini *mini, char *file);

//UTILS
void				print_list(t_env *env_list);
int					array_is_envmpty(char **array);
//SIGNALS
void				make_sigaction(void);
void				check_global_end(void);
void				handler_ctrl_d(t_mini *mini);
void				signal_global(int signum);
void				heredoc_signal_handle(int signal);
void				handle_sigint(int signum, siginfo_t *info, void *context);

//HEREDOC
int					heredoc_check(t_mini *mini, t_cmd *list);
int					heredoc_init(char *ar);
void				handle_redir(t_mini *mini, t_cmd *cmd);
void				replace_cmd(char **cmd, int heredoc_flag, \
					t_mini *mini, int i);
void				disable_quit_signals(void);
void				heredoc_warn(t_mini *mini, char *del, char *line);
char				*here_expansion(t_mini *mini, char *str, int x, int start);
char				*here_exp_ext(t_mini *m, char *str, char *tmp);
char				*getherename(t_mini *mini, char *str, int x);
char				*ft_alljoin(char **str);
void				split_exit_free(int o, t_mini *mini, char *str, char **res);
char				*ft_herestrndup(t_mini *mini, char *s, size_t n, char **r);
char				**split_keep_sep(t_mini *mini, char *str, char sep);
int					count_dollar(char *str);
char				**free_arr_back(char **str, int i);
int					count_split(char *str, char sep);
void				free_exit_heredoc(t_mini *mini, char *str, char *fr_a);
void				sigint_exithere(t_mini *mini, char *line, char *del);
int					h_skip_quote(char *str, int x);
int					check_q_exp(t_mini *mini, char *line);
char				*temp_file(int index, t_mini *mini);
void				handle_redirag(t_mini *mini, char *file, char *token);
int					check_redir_flag(t_cmd *list);
int					has_quotes(char *str);
char				*h_parse_ident(t_mini *m, char *s);

//EXECUTION 
void				minishell_execution_start(t_mini *mini, char **env);
void				exec_cmd_call(t_mini *mini, char **ar_cm, \
					t_cmd *cmd, char **envp);
void				run_parent_exec(t_mini *mini, int i);
void				run_child_exec(t_mini *mini, char **env, t_cmd *cmd, int i);
void				cl_fd(int *pipefd);
void				redirout_sys(char *file, t_mini *mini);
void				redirect_out(char *oper, char *file, t_mini *mini);
void				redirect_in(char *oper, char *file, t_mini *mini);
void				appredirout_sys(char *file, t_mini *mini);
void				heredoc_redir(char *file, t_mini *mini);
void				redirout_sys(char *file, t_mini *mini);
void				redirin_sys(char *file, t_mini *mini);
char				*remove_quotes(char *str);
void				remove_quotes_from_array(char **arr);
void				exit_status(t_mini *minsh, pid_t pid, int com_run);
void				cl_fd(int *pipefd);
char				**fill_clean(char **cmd, int count);
void				shift_if_empty(char **argv);
int					is_all_dollars(const char *str);
int					array_is_empty(t_mini *mini, t_cmd *cmd, char **array);
void				dupandclose(t_mini *mini, int o);

//ERROR_EXIT_FREE
void				free_exit(void);
void				free_2d_array(char **str);
void				ft_free_cmd(t_mini *mini);
void				m_ft_free_env(t_mini *mini, t_env *env);

//UTILS
int					sizeofarry(char **env);
char				*expand_var(t_mini *mini, char *str);
int					is_built(char *cmd);
void				error_msg_b(t_mini *minsh, char *msg, \
					int exit_code, char *com);
char				**clean_cmd(char **cmd, int heredoc_flag, t_mini *mini);
int					ft_lstsizexec(t_cmd *lst);
int					is_redir(char **str);

//FREE FUNCTIONS
void				ft_free_array(char **str);
void				no_cmd_msg(t_mini *mini, char *name);
void				ft_envdelone(t_env *lst, void (*del)(void *));
void				free_exit_procces(t_mini *mini, char *str);
void				ft_free_env(t_env *env);
void				ft_parser_exit(t_mini *mini, char **s0, \
					char *s1, char *s2);
void				ft_empty_pipe(t_mini *mini, t_cmd *tmp, \
					char **s0, int error);

//BUILT IN

void				run_built(t_mini *mini, t_cmd *cmds, char *cmd);
void				ft_cd(t_mini *mini, char **env);
void				ft_env(t_mini *mini);
void				ft_exit(t_mini *mini, char **input);
void				ft_export(t_mini *mini, char **input);
void				export_empty(t_mini *mini);
void				ft_pwd(void);
void				ft_unset(t_mini *mini, char **input);
void				ft_echo(char **inputs);
char				*find_default(t_env *envl);
void				er_cb(char *env, char *msg, int exit_code, char *com);
void				ft_lstadd_front_b(t_env **lst, t_env *new);
int					number_exit(t_mini *mini, char **input);
long				ft_strtol(const char *str, char **endptr);
int					exit_check_arg(t_mini *mini, int number, char **input);
int					prep_atoi(char *str);
int					exit_error_b(t_mini *mini, int x);

//PATH_CHECKS
char				*search_array(t_mini *mini, char **paths, char *name);
char				*find_path_dir(t_mini *mini, char *path_env, char *name);
char				*find_path(t_mini *mini, char **envp);
char				*get_relative_path(t_mini *mini, char *name);
char				*path_extention(t_mini *mini, char *name);
int					unset_path_check(t_mini *mini);
void				*path_lines(t_mini *mini, char *name);

#endif