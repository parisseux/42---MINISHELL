/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avarrett <avarrett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 13:58:03 by pchatagn          #+#    #+#             */
/*   Updated: 2025/02/27 18:27:50 by avarrett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

extern int	g_exit_status;

typedef struct s_shell
{
	char	**var_env;
}	t_shell;

typedef enum e_token_type
{
    WORD,       //  0 Any word (command, argument)
    PIPE,       // 1 |
    REDIR_IN,   // 2 <
    REDIR_OUT,  // 3 >
    HEREDOC,    // 4 <<
    APPEND,     // 5 >>
	SQUOTE,		// 6 ' ' 
	DQUOTE,		// 7 " "
    END 		// 8 \0
}   t_token_type;

typedef struct s_token
{
	char			*value;
	t_token_type	type;
	struct s_token 	*next;
}	t_token ;

typedef struct s_file
{
    int		fd;
    int     type;
    FILE    *file;
    char	*file_name;
}	t_file;

//command
void	cd_command(char *line);
void	easy_command(t_token *lst_token, t_shell *shell);
void	env_command(t_shell *shell, t_token *lst_token, t_file *file);
void	pwd_command(t_file *file);

//echo_command
void	echo_command(t_token *lst_token, int n_flag, t_file *file);
void	echo_single_quote(char **line, t_file *file);
void	echo_double_quote(char **line, t_file *file);
void	echo_no_quote(char **line, t_file *file);
char	*dolar_sign(char **line);
char    *dolar_special_cases(char **line);
int		echo_check_n_flag(char **line);

//command/utils
void    printf_or_fprintf(t_file *file, char **line);
int 	print_or_file(t_token *lst_token);

//utils 
void	ft_free_char_tab(char **tab);
void	skip_space(char **input);
void    print_token_list(t_token *lst_token);
void	msg_error(char *msg, t_token *lst_token);
void	free_token_list(t_token *lst_token);

//parsing 
t_token	*create_token(char *value, t_token_type type);
void	add_token_to_lst(t_token**lst_token, t_token *new_token);
t_token   *tokenisation(char *input);
t_token	*extract_s_quote(char **input);
t_token	*extract_d_quote(char **input);
t_token *ext_word(char **input);
t_token	*extract_out(char **input);
t_token	*extract_in(char **input);
int	check_syntax_error(t_token *lst_token);
int	check_first_last_token(t_token *lst_token);
int	check_synthax_redirection(t_token *lst_token);

//file
char	*filename(t_token *lst_token);
t_file     *open_file(t_token *lst_token, int type);

//exit
void    exit_command(t_token *lst_token, t_shell *shell, char *input);

//expand_var
void    look_for_dolls(t_token *lst_token);

#endif