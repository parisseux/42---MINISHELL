#include "../inc/minishell.h"

void	exec_with_pipe(t_token *lst_token, t_shell *shell, int pipe)
{
	printf("there is at least one pipe\n");
	(void)lst_token;
	(void)shell;
	(void)pipe;
}

//simple redirection au fonctions correpondantes aux buitltin
void	exec_builtin_cmd(t_token *lst_token, t_shell *shell, t_file *file)
{
	if (lst_token->type == 0)
	{
		if (!ft_strncmp(lst_token->value, "env", 4))
			env_command(shell, lst_token, file);
		else if (!ft_strncmp(lst_token->value, "pwd", 4))
			pwd_command(file);
		else if (!ft_strncmp(lst_token->value, "echo", 5))
		{
			if (lst_token->next->type == 8)
				printf("\n");
			else if (!ft_strncmp(lst_token->next->value, "-n", 2))
				echo_command(lst_token->next->next, 1, file);
			else
				echo_command(lst_token->next, 0, file);
		}
		else
		{
			printf("%s: command not found\n", lst_token->value);
			shell->exit = 127;
		}
	}
	if (print_or_file(lst_token))
		fclose(file->file);
}

//creation d'un child process qui va utiliser execve pour executer
//l'executable present dans le bin
void	exec_non_builtin_command(t_token *lst_token, t_shell *shell)
{
	int	pid;

	pid = fork();
	if (pid == -1)
	{
		perror("fork error");
		exit(EXIT_FAILURE);
	}
	if (pid == 0)
		execve_non_builtin(lst_token, shell);
	else
		waitpid(pid, NULL, 0);
}

//3 cas d'executions
//      pas de pipe et builtin cmd
//      pas de pipe et non builtin cmd
//      pipe
void	execution(t_token *lst_token, t_shell *shell)
{
	int	pipe;
	t_file	*file;

	file = NULL;
	if (print_or_file(lst_token))
		file = open_file(lst_token, print_or_file(lst_token));
	pipe = is_pipe(lst_token);
	if (pipe)
	{
		exec_with_pipe(lst_token, shell, pipe);
	}
	else
	{
		if (is_builtin(lst_token))
			exec_builtin_cmd(lst_token, shell, file);
		else
			exec_non_builtin_command(lst_token, shell);
	}
}
