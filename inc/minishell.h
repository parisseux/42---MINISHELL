
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

typedef struct s_shell
{
	char	**var_env;
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
	END
}	t_token_type;

typedef struct s_token
{
	char			*value;
	t_token_type	type;
	struct s_token	*next;
}	t_token;

typedef struct s_file
{
	int		fd;
	int		type;
	FILE	*file;
	char	*file_name;
}	t_file;

//execution 
void	execution(t_token *lst_token, t_shell *shell);
int		is_pipe(t_token *lst_token);
int		is_builtin(t_token *lst_token);
char	*ft_strjoin_paths(char *dir, char *cmd);
char	*get_env_value(char **env, char *key);
char	*find_cmd_path(char *cmd, char **env);
void	execve_non_builtin(t_token *lst_token, t_shell *shell, int fd_out, int fd_in);
char	**find_cmd_args(t_token *lst_token);
int 	is_redir(t_token *lst_token);
void	handle_redir(t_token *lst_token, t_shell *shell, int redir);
int		look_for_fd_output(t_token *lst_token);
int		look_for_fd_input(t_token *lst_token);
void	exec_non_builtin_cmd(t_token *lst_token, t_shell *shell);
void 	builtin_cmd(t_token *lst_token, t_shell *shell, int fd_out);
//command
void	cd_command(char *line, t_shell *shell);
void	exec_builtin_cmd(t_token *lst_token, t_shell *shell);
void	env_command(t_shell *shell, t_token *lst_token, int fd_out);
void	pwd_command(int fd_out);

//echo_command
void	echo_command(t_token *lst_token, int n_flag, int fd_out);
void	echo_single_quote(char **line, int fd_out);
void	echo_double_quote(char **line, int fd_out);
void	echo_no_quote(char **line, int fd_out);
int		echo_check_n_flag(char **line);

//command/utils
void	printf_or_fprintf(t_file *file, char **line);
int		print_or_file(t_token *lst_token);

//utils 
void	ft_free_char_tab(char **tab);
void	skip_space(char **input);
void	print_token_list(t_token *lst_token);
void	msg_error(char *msg, t_token *lst_token);
void	free_token_list(t_token *lst_token);
int		ft_varcmp(const char *s1, const char *s2, size_t n);
void	clean_exit(int exit_status, t_token *lst_token, char **env);

//parsing 
t_token	*create_token(char *value, t_token_type type);
void	add_token_to_lst(t_token**lst_token, t_token *new_token);
t_token	*tokenisation(char *input);
t_token	*extract_s_quote(char **input);
t_token	*extract_d_quote(char **input);
t_token	*ext_word(char **input);
t_token	*extract_out(char **input);
t_token	*extract_in(char **input);
int		check_syntax_error(t_token *lst_token);
int		check_first_last_token(t_token *lst_token);
int		check_synthax_redirection(t_token *lst_token);

//file
char	*filename(t_token *lst_token);
t_file	*open_file(t_token *lst_token, int type);

//exit
void	exit_command(t_token *lst_token, t_shell *shell, char *input);

//exports 
void    print_export(t_shell *shell, int fd_out);
void    add_var_to_env(char **var_env, char *value);
int 	good_varname(char *name);
void    export_command(t_token *lst_token, t_shell *shell, int fd_out);

//expand_var
void	look_for_dolls(t_token *lst_token, t_shell *shell);
char	*find_var(t_shell *shell, char *name, char *value2);
char	*dolar_sign(char **line);
char	*dolar_special_cases(char **line, char *linee, t_shell *shell);

//expand_var_utils
char	*add_special_case(char *name, char *line);
char 	*rm_var(char *value);
char	*add(char *new_value, char *value, int name_len);
int		alphanum_len(char *value);
int		malloc_size(char *new_value, char *value, int name_len);

//unset
void    unset_command(char *line, t_shell *shell);

#endif 