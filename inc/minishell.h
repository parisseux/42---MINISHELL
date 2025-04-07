#ifndef MINISHELL_H
# define MINISHELL_H

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

extern int	g_stop;

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
}	t_token;

// pipe
void	close_all_pipes(int pipefd[][2], int n_pipes);
void	wait_all_pids(int *pids, int *status, int n_cmd);
void	create_all_pipes(int pipefd[][2], int n_pipes);
void	handle_first_cmd(t_token *mini_lst, t_shell *shell,
			int pipefd[][2], int n_pipes);
void	handle_last_cmd(t_token *mini_lst, t_shell *shell,
			int pipefd[][2], int n_pipes);
void	go_to_next_pipe(t_token **lst_token);
t_token	*create_mini_list_token(t_token *lst_token);
t_token	*create_mini_list(t_token **lst_token);
void	handle_middle_cmd(t_token *lst, t_shell *shell,
			int pipefd[][2], int i, int n_pipes);
void	close_all_pipes_except(int pipefd[][2], int i, int n_pipes);

//signals
void	init_signals(void);
void	sigint_handler(int sig);
void	restore_signals(void);
void	signals_heredoc(void);

int		start_minishell(t_shell *shell, char *input);

//execution 
void	execution(t_token *lst_token, t_shell *shell);
int		is_pipe(t_token *lst_token);
int		is_builtin(t_token *lst_token);
char	*ft_strjoin_paths(char *dir, char *cmd);
char	*get_env_value(char **env, char *key);
char	*find_cmd_path(char *cmd, char **env);
void	execve_non_builtin(t_token *lst_token, t_shell *shell);
char	**find_cmd_args(t_token *lst_token);
int		is_redir(t_token *lst_token);
int		is_def(t_token *lst_token);
int		handle_redir(t_token *lst_token, t_shell *shell);
void	handle_heredoc_prompt( int fd_write, char *stop, t_shell *shell);
void	non_builtin_cmd(t_token *lst_token, t_shell *shell);
void	builtin_child_process(t_token *lst_token, t_shell *shell);
void	builtin_parent_process(t_token *lst_token, t_shell *shell);
void	restore_and_close_fd(int saved_stdout, int saved_stdin);
void	exec_one_cmd(t_token *lst_token, t_shell *shell);

//command
void	cd_command(t_token *lst_token, t_shell *shell);
void	exec_builtin_cmd(t_token *lst_token, t_shell *shell);
void	env_command(t_shell *shell, t_token *lst_token);
void	pwd_command(void);
int		extract_exit_status(int status, t_shell *shell);

//echo_command
void	echo_command(t_token *lst_token, int n_flag);
void	echo_single_quote(char **line);
void	echo_double_quote(char **line);
void	echo_no_quote(char **line);
int		echo_check_n_flag(char **line);

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
t_token	*create_token(char *value, t_token_type type);
void	add_token_to_lst(t_token**lst_token, t_token *new_token, int space);
t_token	*tokenisation(char *input);
t_token	*extract_s_quote(char **input);
t_token	*extract_d_quote(char **input);
t_token	*ext_word(char **input);
t_token	*extract_out(char **input);
t_token	*extract_in(char **input);
int		check_syntax_error(t_token *lst_token);
int		check_first_last_token(t_token *lst_token);
int		check_synthax_pipe(t_token *lst_token);
int		check_synthax_redirection(t_token *lst_token);

//exit
void	exit_command(t_token *lst_token, t_shell *shell);

//exports
void	print_export(t_shell *shell);
char	**add_var_to_env(char **var_env, char *value, int shell);
int		good_varname(char *name, char unitl);
void	export_command(t_token *lst_token, t_shell *shell);

//expand_var
void	look_for_dolls(t_token *lst_token, t_shell *shell);
char	*find_var(t_shell *shell, char *name, char *value2);
char	*dolar_sign(char **line);
char	*dol_spec_cases(char **line, char *linee, t_shell *shell);
void	export_message_error(char *value, t_shell *shell);

//expand_var_utils
char	*add_special_case(char *name, char *line);
char	*rm_var(char *value);
char	*add(char *new_value, char *value, int name_len, char symbol);
int		alphanum_len(char *value);
int		malloc_size(char *new_value, char *value, int name_len, char symbol);

//unset
void	unset_command(char *line, t_shell *shell);

//shell_var
void	shell_var(t_token *lst_token, t_shell *shell);
void	prep_var_shell(char ***var);

// detect_var
t_token	*token_var(char **input);
int		detect_var(char *input);
int		in_quote(char pipe_or_else, char *input);

int		not_cmd(t_token *lst_token);

//bin_path
void	execve_bin_token(t_token *lst_token, t_shell *shell);
t_token	*bin_path(char **input);
int		is_bin_path(t_token *lst_token);
void	cmd_not_found(t_token *lst_token);

//expand_home
void	expand_home(t_shell *shell, t_token *lst_token);

void	change_fd(int fd_out, int fd_in);

#endif