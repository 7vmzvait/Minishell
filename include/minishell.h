/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haitaabe <haitaabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 09:28:46 by eazmir            #+#    #+#             */
/*   Updated: 2025/07/06 09:52:16 by haitaabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include "../parsing/parsing.h"

extern int			g_exit_status;
typedef struct s_context
{
	int				prev_pipe;
	int				last_pid;
	char			**env;
	int				fdpipe[2];
	pid_t			pids;
}					t_context;

typedef struct s_shell
{
	char			*value;
	char			*key;
	struct s_shell	*next;
}					t_shell;

typedef struct s_env
{
	t_shell			*env_list;
}					t_env;

void				execute_builtins_no_redir(t_cmd *cmd,t_env *env,t_shell **shell);
int					is_builtn_no_redir(char *cmd);
void				print_exit_error(int option, char **args);
void				setup_heredoc_signals(bool ignore_sigint);
void				kill_process(void);
void				update_env(t_shell **shell, char *args, t_env *env);
char				*check_command(char *cmd, t_env *env);
void				child_process(t_cmd *cmd, t_context *ctx, t_shell *shell,
						t_env *env);
void				free_cmd_list(t_cmd *cmd);
t_env				*init_env(char **env);
void				cleanup_memory(t_cmd *cmd, t_context *ctx, t_env *env,
						t_shell *shell);
void				here_doc(char *del);
int					run_builtins(t_cmd *cmd, t_shell *shell, t_env *env,
						t_context *ctx);
int					execute_builtins(t_cmd *cmd, t_shell *shell, t_env *env);
int					is_builtin_command(char *command);
void				free_env_var_list(t_env *head);
void				signals_handler(void);
void				init_shell(char **env, t_context *ctx, t_shell *shell,
						t_env *env_var);
void				free_cmd_args(t_cmd *cmd);
void				free_env(char **env);
void				handle_signals(int sig);
t_cmd				*parse_input(char *input, t_env *env);
int					redir_infile(t_cmd *cmd);
int					redir_outfile(t_cmd *cmd);
char				*getenv_path(t_env *env);
int					is_builtin_command(char *command);
int					execute_builtins(t_cmd *cmd, t_shell *shell, t_env *env);
int					run_builtins(t_cmd *cmd, t_shell *shell, t_env *env,
						t_context *ctx);
char				**tokenize(char *line, t_env *env);
int					ft_export1(t_shell **shell, char **args, t_env *env);
char				*ft_create_env_line(t_shell *shell);
char				**list_to_array(t_env *env, t_shell *shell);
char				*extract_args(char *args, char opt);
void				join_key(t_shell **shell, char *args, t_env *env);
void				add_back(t_shell **head, t_shell *last);
int					path_len(char **tab);
void				print_export(t_env *env);
t_shell				*create_node(char *args);
char				**ft_sort_tab(char **tab, int len);
char				*join_key_with_value(t_shell *shell);
int					is_valid_export_syntax(char *args);
char				*extract_keys(char *args, char opt);
void				add_node(t_shell **shell, char *last, t_env *env);
void				handle_redir2(t_cmd *cmd, char **tokens, int *i);
int					is_redir(char *tokens);
int					execute_commands(t_cmd *cmd, t_context *ctx, t_shell *shell,
						t_env *env);
int					ft_cd(t_env *env, char **args);
int					ft_exit(t_cmd *cmd);
int					ft_echo(char **args);
int					ft_env(t_env *env, t_shell *shell, char **args);
int					ft_pwd(char **args);
int					ft_unset(t_shell **shell, t_env *env, char **args);
void				ft_export(t_shell **shell, char **env, t_cmd *cmd);
char				**get_env(t_shell *shell);
void				free_split(char **split_path);
char				*get_next_line(int fd);
void				exec(char **cmd, t_shell *shell, t_env *env, t_cmd *cmd2);
#endif
