#include "../inc/minishell.h"

// a modifier --> write au lieu de printf comme exemple de pwd, env
// introduier fd_out avec utilisation de dup() et dup2 comme pour pwd, env

void	echo_command(t_token *lst_token, int n_flag, int fd_out)
{
	char	*line;
	int		type;

	while (lst_token)
	{
		line = lst_token->value;
		type = lst_token->type;
		if (*line)
		{
			if (type == SQUOTE)
				echo_single_quote(&line, fd_out);
			else if (type == DQUOTE)
				echo_double_quote(&line, fd_out);
			else
				echo_no_quote(&line, fd_out);
		}
		if (lst_token->type == END)
		{
			if (n_flag == 0)
				write(STDOUT_FILENO, "\n", 1);
		}
		else if (lst_token->next->type != END)
			write(STDOUT_FILENO, " ", 1);
		lst_token = lst_token->next;
	}
}

void	echo_single_quote(char **line, int fd_out)
{
	int	saved_stdout;

	saved_stdout = dup(STDOUT_FILENO);
	if (fd_out != -1)
	{
		dup2(fd_out, STDOUT_FILENO);
		close(fd_out);
	}
	write (STDOUT_FILENO, *line, ft_strlen(*line));
	dup2(saved_stdout, STDOUT_FILENO);
	close(saved_stdout);
}
// if (**line == '\'')
// 	(*line)++; rajouter commme dans expand_var ??

void	echo_double_quote(char **line, int fd_out)
{
	int	saved_stdout;

	saved_stdout = dup(STDOUT_FILENO);
	if (fd_out != -1)
	{
		dup2(fd_out, STDOUT_FILENO);
		close(fd_out);
	}
	write(STDOUT_FILENO, *line, ft_strlen(*line));
	dup2(saved_stdout, STDOUT_FILENO);
	close(saved_stdout);
}

// while (**line)
// {
// 	if (**line == '\\')
// 	{
// 		(*line)++;
// 		if (**line == '\\' || **line == '$' || **line == '`')
// 			printf_or_fprintf(file, line);
// 		else
// 		{
// 			if (file != NULL)
// 				fprintf(file->file, "\\%c", **line);
// 			else
// 				printf("\\%c", **line);				
// 		}
// 		line++;
// 	}
// }

void	echo_no_quote(char **line, int fd_out)
{
	int	saved_stdout;

	saved_stdout = dup(STDOUT_FILENO);
	if (fd_out != -1)
	{
		dup2(fd_out, STDOUT_FILENO);
		close(fd_out);
	}
	write(STDOUT_FILENO, *line, ft_strlen(*line));
	dup2(saved_stdout, STDOUT_FILENO);
	close(saved_stdout);
}

// while (**line)
// {
// 	if (**line == '\\')
// 	{
// 		(*line)++;
// 		if (**line)
// 		{
// 			if (file != NULL)
// 				fprintf(file->file, "\\%c", **line);
// 			else
// 				printf("\\%c", **line);
// 			(*line)++;
// 		}
// 	}
// }

int	echo_check_n_flag(char **line)
{
	int	n_flag;

	n_flag = 0;
	while (**line == '-' && *((*line) + 1) == 'n')
	{
		(*line) += 2;
		n_flag = 1;
	}
	return (n_flag);
}
