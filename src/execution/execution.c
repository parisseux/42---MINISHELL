#include "../inc/minishell.h"

void	exec_with_pipe(t_token *lst_token, t_shell *shell, int pipe)
{
	printf("there is at least one pipe\n");
	(void)lst_token;
	(void)shell;
	(void)pipe;
}

//division de la fonction pour handle les redirction dans le cas d'une cmd builtin
void	exec_builtin_cmd(t_token *lst_token, t_shell *shell)
{
	int redir;

	redir = is_redir(lst_token);
	if (redir)
		handle_redir(lst_token, shell, 1);
	else
		builtin_cmd(lst_token, shell, -1);
}

//considere les redirections si presente avant d'executer
//creation d'un child process qui va utiliser execve pour executer
//l'executable present dans le bin
void	exec_non_builtin_cmd(t_token *lst_token, t_shell *shell)
{
	int	pid;
	int redir;

	pid = fork();
	redir = is_redir(lst_token);
	if (pid == -1)
	{
		perror("fork error");
		exit(EXIT_FAILURE);
	}
	if (pid == 0 && redir)
		handle_redir(lst_token, shell, 0);
	else if (pid == 0)
		execve_non_builtin(lst_token, shell, -1, -1);
	else
		waitpid(pid, NULL, 0);
}

//divise l'execution en trois
//      pas de pipe et builtin cmd
//      pas de pipe et non builtin cmd
//      pipe
void	execution(t_token *lst_token, t_shell *shell)
{
	int	pipe;

	pipe = is_pipe(lst_token);
	if (pipe)
	{
		exec_with_pipe(lst_token, shell, pipe);
	}
	else
	{
		if (is_builtin(lst_token))
			exec_builtin_cmd(lst_token, shell);
		else
			exec_non_builtin_cmd(lst_token, shell);
	}
}
