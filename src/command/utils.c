/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avarrett <avarrett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 13:16:01 by avarrett          #+#    #+#             */
/*   Updated: 2025/02/25 13:27:18 by avarrett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void    printf_or_fprintf(t_file *file, char **line)
{
    if (file != NULL)
		fprintf(file->file, "%c", **line);
	else
		printf("%c", **line);
}
