/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchatagn <pchatagn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 16:24:32 by pchatagn          #+#    #+#             */
/*   Updated: 2025/05/01 16:24:33 by pchatagn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

//ajjouter quote
void	builtin_parent_process(t_token *lst_token,
	t_shell *shell)
{
	t_token	*temp;
	int		stop;

	stop = -1;
	temp = lst_token;
	while (temp->type != END && stop == -1)
	{
		if ((temp->type == WORD || temp->type == SQUOTE
				|| temp->type == DQUOTE) && !ft_strncmp(temp->value, "cd", 3))
			stop = cd_command(temp->next, shell);
		else if ((temp->type == WORD || temp->type == SQUOTE
				|| temp->type == DQUOTE)
			&& !ft_strncmp(temp->value, "export", 7))
			stop = export_command(temp, shell);
		else if ((temp->type == WORD || temp->type == SQUOTE
				|| temp->type == DQUOTE)
			&& !ft_strncmp(temp->value, "unset", 6))
			stop = unset_command(temp->next, shell);
		else if ((temp->type == WORD || temp->type == SQUOTE
				|| temp->type == DQUOTE)
			&& !ft_strncmp(temp->value, "exit", 5))
			stop = exit_command(lst_token, shell);
		temp = temp->next;
	}
	shell->exit = stop;
}

void	builtin_child_action(t_token *lst_token, t_shell *shell)
{
	t_token	*temp;
	int		stop;

	stop = -1;
	temp = lst_token;
	while (temp->type != END && stop == -1)
	{
		if ((temp->type == WORD || temp->type == SQUOTE
				|| temp->type == DQUOTE) && !ft_strncmp(temp->value, "env", 4))
			stop = env_command(shell, lst_token);
		else if ((temp->type == WORD || temp->type == SQUOTE
				|| temp->type == DQUOTE) && !ft_strncmp(temp->value, "pwd", 4))
			stop = pwd_command();
		else if ((temp->type == WORD || temp->type == SQUOTE
				|| temp->type == DQUOTE)
			&& !ft_strncmp(temp->value, "echo", 5))
			stop = start_echo(lst_token);
		temp = temp->next;
	}
	exit(stop);
}

void	builtin_child_process(t_token *lst_token, t_shell *shell)
{
	int		pid;
	int		status;

	pid = fork();
	if (pid == 0)
		builtin_child_action(lst_token, shell);
	else
	{
		waitpid(pid, &status, 0);
		extract_exit_status(status, shell);
	}
}

void	restore_and_close_fd(int saved_stdout, int saved_stdin)
{
	dup2(saved_stdout, STDOUT_FILENO);
	dup2(saved_stdin, STDIN_FILENO);
	close(saved_stdin);
	close(saved_stdout);
}
