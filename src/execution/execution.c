#include "../inc/minishell.h"

//je ferai plus tard quand les execution builtin et
// non builtin avec redirection sreont bonnes
void	exec_with_pipe(t_token *lst_token, t_shell *shell)
{
	//separate_cmd(lst_token);
	// int pipe_fds[2];
	// int pid;

	// pipe_fds[0] = -1;
	// pipe_fds[1] = -1;
	// if (pipe(pipe_fds) == -1)
	// 	return (perror("pipe"), -1);
	// pid  = fork();
	// if (pid < 0)
	// {
	// 	close(pipe_fds[0]);
	// 	close(pipe_fds[1]);
	// 	return (perror("fork"), -1);
	// }
	// else if (pid = 0)
	// {
	//	restore_Signals();	
	// 	ft_putstr_fd("child process in pipe", 1);
	// 	exit(0);
	// }
	// waitpid(pid, NULL, 0);
	// printf("there is at least one pipe\n");
	// printf("test avec une seule pipe\n");
	(void)shell;
	(void)lst_token;
}

//creation d'un child process qui va utiliser execve pour executer
//l'executable present dans le bin
void	non_builtin_cmd(t_token *lst_token, t_shell *shell, int fd_in, int fd_out)
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
		execve_non_builtin(lst_token, shell, fd_out, fd_in);
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
void	builtin_cmd(t_token *lst_token, t_shell *shell, int fd_out)
{
	t_token	*temp;

	temp = lst_token;
	while (temp->type != END)
	{
		if (temp->type == WORD || temp->type == DEF)
		{
			if (!ft_strncmp(temp->value, "cd", 3)
				|| !ft_strncmp(temp->value, "export", 7)
				|| !ft_strncmp(temp->value, "unset", 6)
				|| !ft_strncmp(temp->value, "exit", 5))
			{
				builtin_parent_process(lst_token, shell, fd_out);
				return ;
			}
			else if (!ft_strncmp(temp->value, "echo", 5)
				|| !ft_strncmp(temp->value, "pwd", 4)
				|| !ft_strncmp(temp->value, "env", 4))
			{
				builtin_child_process(lst_token, shell, fd_out);
				return ;
			}
		}
		temp = temp->next;
	}
}

//divise l'execution en trois
//      pas de pipe et builtin cmd
//      pas de pipe et non builtin cmd
//      pipe
void	execution(t_token *lst_token, t_shell *shell)
{
	int	fd_in;
	int	fd_out;

	fd_in = -1;
	fd_out = -1;
	if (is_pipe(lst_token))
	{
		exec_with_pipe(lst_token, shell);
	}
	else
	{
		if (handle_redir(lst_token, &fd_in, &fd_out, shell) == 1)
		 	return ;
		if (is_def(lst_token) && ft_strncmp(lst_token->value, "export", 7))
			return ;
		if (is_builtin(lst_token))
			builtin_cmd(lst_token, shell, fd_out);
		else
			non_builtin_cmd(lst_token, shell, fd_in, fd_out);
	}
}
