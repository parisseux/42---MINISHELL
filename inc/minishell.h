#ifndef MINISHELL_H
# define MINISHELL_H
# define _POSIX_C_SOURCE 200809L
# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
# include <signal.h>
# include <ctype.h>
# include "../libft/libft.h"
# include <sys/types.h>
# include <sys/wait.h>

extern volatile sig_atomic_t	g_last_signal;

typedef struct s_shell
{
	char	**var_env;
	char	**shell_env;
	int		exit;
}	t_shell;

typedef enum e_token_type
{
	WORD,
	PIPE,
	REDIR_IN,
	REDIR_OUT,
	HEREDOC,
	APPEND,
	SQUOTE,
	DQUOTE,
	DEF,
	BIN,
	END
}	t_token_type;

typedef struct s_token
{
	char			*value;
	int				space;
	t_token_type	type;
	struct s_token	*next;
	int				fd_hd;
}	t_token;

typedef struct s_pipe
{
	int		**pipefd;
	int		*pids;
	int		n_pipes;
	t_token	**cmds;
}	t_pipe;

// pipe
void	close_all_pipe(t_pipe *p);
void	wait_all_pids(t_pipe *p, t_shell *shell);
void	create_all_pipes(int **pipefd, int n_pipes);
void	handle_last_cmd(t_pipe *p, t_shell *shell);
void	handle_first_cmd(t_pipe *p, t_shell *shell);
void	go_to_next_pipe(t_token **lst_token);
t_token	*create_mini_list_token(t_token *lst_token);
t_token	*create_mini_list(t_token **lst_token);
void	handle_middle_cmd(t_pipe *p, t_shell *shell, int i);
void	close_all_pipes_except(int **pipefd, int i, int n_pipes);
void	free_cmds_lst(t_pipe *p);
void	fork_and_exec_pipe(t_pipe *p, t_shell *shell);
void	create_pipe_and_mini_lst(t_pipe *p, t_token *lst_token);
int		init_pipe_data(t_pipe *p, int n_pipes);

//signals
void init_parent_signals(void);
void	init_exec_child_signals(void);
void	mute_parent_signals(int on);
void	init_heredoc_child_signals(void);
void    cleanup_readline(void);
void	parent_sigint(int signo);

int		start_minishell(t_shell *shell, char *input);

//execution 
void	execution(t_token *lst_token, t_shell *shell);
int		is_pipe(t_token *lst_token);
int		is_builtin(t_token *lst_token);
char	*ft_strjoin_paths(char *dir, char *cmd);
char	*env_value(t_shell *shell, char **env, char *key);
char	*find_cmd_path(t_shell *shell, char *cmd, char **env);
void	execve_non_builtin(t_token *lst_token, t_shell *shell);
char	**find_cmd_args(t_token *lst_token);
int		is_redir(t_token *lst_token);
int		is_def(t_token *lst_token);
int		handle_redir(t_token *lst_token, t_shell *shell);
void	heredoc_child(int pipefd, t_token *lst_token, t_shell *shell);
void	non_builtin_cmd(t_token *lst_token, t_shell *shell);
void	builtin_child_process(t_token *lst_token, t_shell *shell);
void	builtin_parent_process(t_token *lst_token, t_shell *shell);
void	restore_and_close_fd(int saved_stdout, int saved_stdin);
void	exec_one_cmd(t_token *lst_token, t_shell *shell);
void	close_heredoc(t_token *lst);
int prepare_heredocs(t_token *lst, t_shell *shell);
int build_heredoc(t_token *lst, int *fd, t_shell  *shell);

//command/utils
int		print_or_file(t_token *lst_token);

//utils
void	ft_free_char_tab(char **tab);
int		skip_space(char **input);
int		spaces(char input);
void	print_token_list(t_token *lst_token);
void	msg_error(char *msg, t_token *lst_token);
void	free_token_list(t_token *lst_token);
int		ft_varcmp(const char *s1, const char *s2, size_t n);
void	clean_exit(int exit_status, t_token *lst_token,
			char **env, char **shell);
void	cmd_err(char *msg, char *cmd, int exit, t_shell *shell);

//parsing
t_token	*create_token(char *value, t_token_type type, int fd_out);
void	add_token_to_lst(t_token**lst_token, t_token *new_token, int space);
t_token	*tokenisation(char *input);
t_token	*extract_s_quote(char **input);
t_token	*extract_d_quote(char **input);
t_token	*ext_word(char **input);
t_token	*extract_out(char **input);
t_token	*extract_in(char **input);
int		check_syntax_error(t_token *lst_token);
t_token *parse_pipe(char **input);

/////////////////////////////////////// COMMAND ///////////////////////////////////////

//echo
void	echo_command(t_token *lst_token);
void	echo_single_quote(char **line);
void	echo_double_quote(char **line);
void	echo_no_quote(char **line);
int		start_echo(t_token *lst_token);

//exit
int		exit_command(t_token *lst_token, t_shell *shell);
void	exit_message(t_shell *shell, t_token *exit);
int		extract_exit_status(int status, t_shell *shell);
int		valid_exit_type(int type);

//export
void	print_export(t_shell *shell);
char	**add_var_to_env(char **var_env, char *value);
int		good_varname(char *name, char unitl);
int		export_command(t_token *lst_token, t_shell *shell);

//export_utils
int		found_in_tab(char **var_env, char *value, int len);
int		bad_export(char	*value);
int		invalid_export_type(int type);
int		tab_len(char **tab);
void	export_message_error(char *value, t_shell *shell);

//unset
int		unset_command(t_token *lst, t_shell *shell);

//cd
int		cd_command(t_token *lst_token, t_shell *shell);

//env
int		env_command(t_shell *shell, t_token *lst_token);

//pwd
int		pwd_command(void);

/////////////////////////////////////// PARSING ///////////////////////////////////////

//expand_var
void	look_for_dolls(t_token *lst_token, t_shell *shell);
void	find_var(t_shell *shell, char *name, char **value, int len);
char	*dolar_sign(char *line, int index);
void	which(char **value, t_shell *shell);
void	dol_spec_cases(char **value, int index, char *line, t_shell *shell);

//expand_var_utils
char	*add_special_case(char *name, char *line);
char	*rm_var(char *value, int name_len);
char	*add(char *new, char *value, int len);
int		alphanum_len(char *value);
int		malloc_size(char *new_value, char *value, int name_len);

//expand_var_utils2
static void	handle_valid_token(t_token *lst_token, t_shell *shell);
int		spe_case(char *value, int type, int space);

//shell_var
int		shell_var(t_token *lst_token, t_shell *shell);
void	prep_var_shell(char ***var);
int		len_var(char *value);
int		shell_var(t_token *lst_token, t_shell *shell);

//valid_shell_var
int 	in_shell_env(t_token *lst);

//detect_var
t_token	*token_var(char **input);
int		detect_var(char *input);
int		in_quote(char pipe_or_else, char *input);
int		closed_quotes(char *copy, char quote, int i);
char	*rm_quotes(char *input);

//detect_var_utils
int		not_cmd(t_token *lst_token);
void	quote_msg(char c);
int		closed_quotes(char *copy, char quote, int i);
int		detect_var(char *input);

//bin_path
void	execve_bin_token(t_token *lst_token, t_shell *shell);
t_token	*bin_path(char **input);
int		is_bin_path(t_token *lst_token);
void	cmd_not_found(t_token *lst_token);

//expand_home
int		space(t_token *lst_token);
char	*add_home(char *home, char *str);
void	home_not_set(t_shell *shell);
void	replace_home(t_shell *shell, t_token *lst);

// expand_home_u
int		ishome(char *str, int i);
int		before(t_token *lst_token);
int		isvalid(int type, char *str);
void	init(int *i, char **name, char **dup, char *value);

// 
void	change_fd(int fd_out, int fd_in);
char	*look_for_cmd(t_token **temp, t_shell *shell);
int		non_builtin_child(t_token *lst_token, t_shell *shell);
int		heredoc_parent(int pipefd, int pid, t_shell *shell);
int		not_cmd(t_token *lst_token);
void	exec_builtin_cmd(t_token *lst_token, t_shell *shell);
char	*find_pid();

#endif