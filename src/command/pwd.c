/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avarrett <avarrett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 13:02:27 by parissachat       #+#    #+#             */
/*   Updated: 2025/02/26 16:10:41 by avarrett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	pwd_command(t_file *file)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	if (file)
		fprintf(file->file, "%s\n", pwd);
	else
		printf("%s\n", pwd);
	free(pwd);		
}
