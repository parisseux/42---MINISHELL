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

//creation d'un child process qui va utiliser execve pour executer
//l'executable present dans le bin
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
		restore_signals();
		execve_non_builtin(lst_token, shell);
	}	
	else
	{
		waitpid(pid, &status, 0);
		extract_exit_status(status, shell);
	}
}

//builtin qui necessitent stdout: echo, pwd, export, env
//builtin  qui ncesstient stdin: aucune donc pas besoins de gere < et <<
//run in a forked child: echo, pwd, env
//run in parent (change de state): cd, export, unset and exit
void	builtin_cmd(t_token *lst_token, t_shell *shell)
{
	t_token	*temp;
	int		saved_stdout;
	int		saved_stdin;

	temp = lst_token;
	saved_stdout = dup(STDOUT_FILENO);
	saved_stdin = dup(STDIN_FILENO);
	if (handle_redir(lst_token, shell) == 1)
		return ;
	while (temp->type != END)
	{
		if (temp->type == WORD)
		{
			if (!ft_strncmp(temp->value, "cd", 3)
				|| !ft_strncmp(temp->value, "export", 7)
				|| !ft_strncmp(temp->value, "unset", 6)
				|| !ft_strncmp(temp->value, "exit", 5))
			{
				builtin_parent_process(lst_token, shell);
				restore_and_close_fd(saved_stdout, saved_stdin);
				return ;
			}
			else if (!ft_strncmp(temp->value, "echo", 5)
				|| !ft_strncmp(temp->value, "pwd", 4)
				|| !ft_strncmp(temp->value, "env", 4))
			{
				builtin_child_process(lst_token, shell);
				restore_and_close_fd(saved_stdout, saved_stdin);
				return ;
			}
		}
		temp = temp->next;
	}
	restore_and_close_fd(saved_stdout, saved_stdin);
}

void	exec_one_cmd(t_token *lst_token, t_shell *shell)
{
	if (is_builtin(lst_token))
		builtin_cmd(lst_token, shell);
	else
	{
		if (handle_redir(lst_token, shell) == 1)
			return ;
		if (is_def(lst_token))
			return ;
		non_builtin_cmd(lst_token, shell);
	}
}

//divise l'execution en trois
//      pas de pipe et builtin cmd
//      pas de pipe et non builtin cmd
//      pipe
void	execution(t_token *lst_token, t_shell *shell)
{
	if (is_pipe(lst_token))
		exec_with_pipe(lst_token, shell, is_pipe(lst_token));
	else
		exec_one_cmd(lst_token, shell);
}
