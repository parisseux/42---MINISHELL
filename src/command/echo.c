/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avarrett <avarrett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 15:50:36 by parissachat       #+#    #+#             */
/*   Updated: 2025/02/26 15:01:37 by avarrett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int 	print_or_file(t_token *lst_token)
{
	t_token *tmp = lst_token;
	
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
	char	*line = lst_token->next->value; 
	int		type = lst_token->next->type;

	while (*line) 
	{
		if (type == DQUOTE)
			echo_double_quote(&line, file);
		else if (type == SQUOTE)
			echo_single_quote(&line, file);
		else
			echo_no_quote(&line, file);
		if (!n_flag && !file)
			printf("\n");
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
		else if (**line == '$')
			echo_dolar_sign(line);
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
		if (**line == '$')
			echo_dolar_sign(line);
		else if (**line == '\\')
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
