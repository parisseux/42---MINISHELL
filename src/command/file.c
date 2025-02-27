/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avarrett <avarrett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 19:00:37 by ninisse           #+#    #+#             */
/*   Updated: 2025/02/27 11:51:12 by avarrett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	*filename(t_token *lst_token)
{
	t_token *tmp = lst_token;
	
	while (tmp)
	{	
		if (tmp->type == APPEND || tmp->type == REDIR_OUT)
			return (tmp->next->value);
		tmp = tmp->next;
	}
	return (NULL);
}

t_file     *open_file(t_token *lst_token, int type)
{
    t_file *file;

    file = malloc(sizeof(t_file));
	file->file_name = filename(lst_token);
    file->type = type;
    if (file->file_name == NULL)
	{
		free(file);
		return (NULL);
	}
    if (type == APPEND)
        file->file = fopen(file->file_name, "a");
    else
        file->file = fopen(file->file_name, "w");
    if (file->file == NULL)
    {
        printf("fopen failed\n");
        free(file);
        return (NULL);
    }
    file->fd = fileno(file->file);
    if (file->fd == -1)
    {
        printf("fileno failed\n");
        fclose(file->file);
        free(file);
        return (NULL);
    }
    return (file);
}
