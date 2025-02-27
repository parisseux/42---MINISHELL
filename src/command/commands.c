/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avarrett <avarrett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 18:58:31 by avarrett          #+#    #+#             */
/*   Updated: 2025/02/27 11:35:01 by avarrett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

// which command a modifier pour faire un else (no command found)
// test

void	easy_command(t_token *lst_token, t_shell *shell)
{
	t_file	*file;
	
	file = NULL;
	if (print_or_file(lst_token))
		file = open_file(lst_token, print_or_file(lst_token));
	if (lst_token->type == 0)
	{
		if(!ft_strncmp(lst_token->value, "env", 3))
			env_command(shell, lst_token, file);
		else if(!ft_strncmp(lst_token->value, "pwd", 3))
			pwd_command(file);
		else if (!ft_strncmp(lst_token->value, "echo", 4) && ft_strlen(lst_token->value) == 4)
		{
			if (lst_token->next->type == 8)
				printf("\n");
			else if (!ft_strncmp(lst_token->next->value, "-n", 2))
				echo_command(lst_token->next, 1, file);
			else
				echo_command(lst_token, 0, file);
		}
		else
			printf("%s: command not found", lst_token->value);
	}
	if (print_or_file(lst_token))
		fclose(file->file);
}


