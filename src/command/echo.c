#include "../inc/minishell.h"

int	print_or_file(t_token *lst_token)
{
	t_token	*tmp;
	
	tmp = lst_token;
	while (tmp)
	{	
		if (tmp->type == APPEND || tmp->type == REDIR_OUT)
			return (tmp->type);
		tmp = tmp->next;
	}
	return (0);
}

void	echo_command(t_token *lst_token, int n_flag, t_file *file)
{
	char	*line;
	int		type;
	char	*space;
	char	*space2;

	space = " ";
	space2 = "\n";
	while (lst_token)
	{
		line = lst_token->value;
		type = lst_token->type;
		while (*line)
		{
			if (type == SQUOTE)
				echo_single_quote(&line, file);
			else if (type == DQUOTE)
				echo_double_quote(&line, file);
			else
				echo_no_quote(&line, file);
		}
		if (lst_token->type == END)
		{
			if (n_flag == 0)
				printf_or_fprintf(file, &space2);
			break;
		}
		else
			printf_or_fprintf(file, &space);
		lst_token = lst_token->next;
	}
}

void	echo_single_quote(char **line, t_file *file)
{
	if (file != NULL && file->type == APPEND)
		fprintf(file->file, "\n");
	while (**line)
	{
		printf_or_fprintf(file, line);
		(*line)++;
	}
	if (**line == '\'')
		(*line)++;

}

void	echo_double_quote(char **line, t_file *file)
{
	if (file != NULL && file->type == APPEND)
		fprintf(file->file, "\n");
	while (**line)
	{
		if (**line == '\\')
		{
			(*line)++;
			if (**line == '\\' || **line == '$' || **line == '`')
				printf_or_fprintf(file, line);
			else
			{
				if (file != NULL)
					fprintf(file->file, "\\%c", **line);
				else
					printf("\\%c", **line);				
			}
			line++;
		}
		else
		{
			printf_or_fprintf(file, line);
			(*line)++;
		}
	}
}

void	echo_no_quote(char **line, t_file *file)
{
	if (file != NULL && file->type == APPEND)
		fprintf(file->file, "\n");
	while (**line)
	{
		if (**line == '\\')
		{
			(*line)++;
			if (**line)
			{
				if (file != NULL)
					fprintf(file->file, "\\%c", **line);
				else
					printf("\\%c", **line);
				(*line)++;
			}
		}
		else
		{
			printf_or_fprintf(file, line);
			(*line)++;
		}
	}
}
