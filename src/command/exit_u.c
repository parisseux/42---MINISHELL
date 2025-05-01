/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_u.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avarrett <avarrett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 16:24:15 by pchatagn          #+#    #+#             */
/*   Updated: 2025/05/01 17:20:08 by avarrett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	extract_exit_status(int status, t_shell *shell)
{
	if (WIFEXITED(status))
		shell->exit = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		shell->exit = 128 + WTERMSIG(status);
	else
		shell->exit = 0;
	if (shell->exit == 0)
		return (0);
	else
		return (1);
}

void	exit_message(t_shell *shell, t_token *exit)
{
	write(STDERR_FILENO, "minishell: exit: numeric argument required\n", 43);
	clean_exit(2, exit, shell->venv, shell->shell_env);
}

int	valid_exit_type(int type)
{
	if (type == WORD || type == SQUOTE || type == DQUOTE
		|| type == BIN || type == DEF)
		return (1);
	return (0);
}
