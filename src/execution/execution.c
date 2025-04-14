#include "../inc/minishell.h"

//pipefd[0] → is the reading end 📖
// pipefd[1] → is the writing end ✍️
void	exec_with_pipe(t_token *lst_token, t_shell *shell, int n_pipes)
{
	int		pipefd[n_pipes + 1][2];
	int		status;
	int		pids[n_pipes + 1];
	int		i;
	t_token	*cmds[n_pipes + 2];

	ft_memset(pipefd, 0, sizeof(pipefd));
	i = 0;
	while (i < n_pipes + 1)
	{
		cmds[i] = create_mini_list(&lst_token);
		i++;
	}
	cmds[n_pipes + 1] = NULL;
	create_all_pipes(pipefd, n_pipes);
	i = 0;
	while (i < n_pipes + 1)
	{
		pids[i] = fork();
		if (pids[i] == 0)
		{
			if (i == 0)
				handle_first_cmd(cmds[i], shell, pipefd, n_pipes);
			else if (i == n_pipes)
				handle_last_cmd(cmds[i], shell, pipefd, n_pipes);
			else
				handle_middle_cmd(cmds[i], shell, pipefd, i, n_pipes);
		}
		i++;
	}
	i = 0;
	while (i < n_pipes + 1)
	{
		free_token_list(cmds[i]);
		i++;
	}
	close_all_pipes(pipefd, n_pipes);
	wait_all_pids(pids, &status, n_pipes + 1);
	extract_exit_status(status, shell);
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
		if (handle_redir(lst_token, shell) == 1)
			return ;
		if (is_def(lst_token))
			return ;
		signal(SIGQUIT, siguit_handler);
		if (is_bin_path(lst_token))
			execve_bin_token(lst_token, shell);
		else
			execve_non_builtin(lst_token, shell);
	}	
	else
	{
		signal(SIGINT, sigint_handler_exec);
		signal(SIGQUIT, siguit_handler);
		waitpid(pid, &status, 0);
		extract_exit_status(status, shell);
		init_signals();
	}
}

void	builtin_cmd(t_token *lst_token, t_shell *shell)
{
	t_token	*temp;

	temp = lst_token;
	while (temp->type != END)
	{
		if (temp->type == WORD && (!ft_strncmp(temp->value, "cd", 3)
			|| !ft_strncmp(temp->value, "export", 7)
			|| !ft_strncmp(temp->value, "unset", 6)
			|| !ft_strncmp(temp->value, "exit", 5)))
		{
			builtin_parent_process(lst_token, shell);
			return ;
		}
		else if (temp->type == WORD && (!ft_strncmp(temp->value, "echo", 5)
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
		if (handle_redir(lst_token, shell) == 1)
			return ;
		builtin_cmd(lst_token, shell);
		restore_and_close_fd(saved_stdout, saved_stdin);
	}
	else
	{
		// saved_stdout = dup(STDOUT_FILENO);
		// saved_stdin = dup(STDIN_FILENO);
		// if (handle_redir(lst_token, shell) == 1)
		// 	return ;
		non_builtin_cmd(lst_token, shell);
		// restore_and_close_fd(saved_stdout, saved_stdin);
	}
		
}

void	execution(t_token *lst_token, t_shell *shell)
{
	if (is_pipe(lst_token))
		exec_with_pipe(lst_token, shell, is_pipe(lst_token));
	else
		exec_one_cmd(lst_token, shell);
}
