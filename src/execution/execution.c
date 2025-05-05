/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchatagn <pchatagn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 16:24:38 by pchatagn          #+#    #+#             */
/*   Updated: 2025/05/05 14:43:15 by pchatagn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	exec_with_pipe(t_token *lst_token, t_shell *shell, int n_pipes)
{
	t_pipe	pipe_data;

	if (init_pipe_data(&pipe_data, n_pipes) != 0)
		return ;
	create_pipe_and_mini_lst(&pipe_data, lst_token);
	fork_and_exec_pipe(&pipe_data, shell);
	free_cmds_lst(&pipe_data);
	close_all_pipe(&pipe_data);
	wait_all_pids(&pipe_data);
}

void	non_builtin_cmd(t_token *lst_token, t_shell *shell)
{
	int	pid;
	int	status;

	pid = fork();
	if (pid == -1)
	{
		perror("fork error");
		exit(EXIT_FAILURE);
	}
	else if (pid == 0)
	{
		if (non_builtin_child(lst_token, shell))
			return ;
	}
	else
	{
		mute_parent_signals(1);
		waitpid(pid, &status, 0);
		mute_parent_signals(0);
		extract_exit_status(status, shell);
	}
}

void	builtin_cmd(t_token *lst_token, t_shell *shell)
{
	t_token	*temp;

	temp = lst_token;
	while (temp->type != END)
	{
		if ((temp->type == WORD || temp->type == SQUOTE
				|| temp->type == DQUOTE) && (!ft_strncmp(temp->value, "cd", 3)
				|| !ft_strncmp(temp->value, "export", 7)
				|| !ft_strncmp(temp->value, "unset", 6)
				|| !ft_strncmp(temp->value, "exit", 5)))
		{
			builtin_parent_process(lst_token, shell);
			return ;
		}
		else if ((temp->type == WORD || temp->type == SQUOTE
				|| temp->type == DQUOTE) && (!ft_strncmp(temp->value, "echo", 5)
				|| !ft_strncmp(temp->value, "pwd", 4)
				|| !ft_strncmp(temp->value, "env", 4)))
		{
			builtin_child_process(lst_token, shell);
			return ;
		}
		temp = temp->next;
	}
}

void	exec_one_cmd(t_token *lst_token, t_shell *shell)
{
	int		saved_stdout;
	int		saved_stdin;

	if (is_builtin(lst_token))
	{
		saved_stdout = dup(STDOUT_FILENO);
		saved_stdin = dup(STDIN_FILENO);
		if (handle_redir(lst_token, shell))
			return ;
		builtin_cmd(lst_token, shell);
		restore_and_close_fd(saved_stdout, saved_stdin);
	}
	else
		non_builtin_cmd(lst_token, shell);
}

void	execution(t_token *lst_token, t_shell *shell)
{
	if (prepare_heredocs(lst_token, shell) == -1)
	{
		shell->exit = 130;
		close_heredoc(lst_token);
		return ;
	}
	if (is_pipe(lst_token))
		exec_with_pipe(lst_token, shell, is_pipe(lst_token));
	else
		exec_one_cmd(lst_token, shell);
	close_heredoc(lst_token);
}
