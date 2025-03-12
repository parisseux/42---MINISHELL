#include "../inc/minishell.h"

//je ferai plus tard quand les execution builtin et
// non builtin avec redirection sreont bonnes
void	exec_with_pipe(t_token *lst_token, t_shell *shell, int fd_in, int fd_out)
{	
	printf("there is at least one pipe\n");
	printf("test avec une seule pipe\n");
	(void)shell;
	(void)fd_in;
	(void)fd_out;
	(void)lst_token;
}

//considere les redirections si presente avant d'executer
//creation d'un child process qui va utiliser execve pour executer
//l'executable present dans le bin
void	non_builtin_cmd(t_token *lst_token, t_shell *shell, int fd_in, int fd_out)
{
	int	pid;

	pid = fork();
	if (pid == -1)
	{
		perror("fork error");
		exit(EXIT_FAILURE);
	}
	else if (pid == 0)
		execve_non_builtin(lst_token, shell, fd_out, fd_in);
	else
		waitpid(pid, NULL, 0);
}

//attribution to the cmd echo, cd, pwd, export, unset, env, exit
//and if redierction fd_out is beinf passed to the cmd
//if no redirection fd = -1 
//builtin qui necessitent stdout: echo, pwd, export, env
//builtin  qui ncesstient stdin: aucune donc pas besoins de gere < et <<
//seul truc a gerer est si le file ou directory
//quil veut ouvrrir n'exsite pas alors rreur
//pour plus tard -> introduction de pipe
//run in a forked child: echo, pwd, env
//run in parent (change de state): cd, export, unset and exit
void	builtin_cmd(t_token *lst_token, t_shell *shell, int fd_out)
{
	t_token	*temp;

	temp = lst_token;
	while (temp->type != END)
	{
		if (temp->type == WORD)
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
	int	pipe;
	int	fd_in;
	int	fd_out;

	fd_in = -1;
	fd_out = -1;
	handle_redir(lst_token, &fd_in, &fd_out);
	pipe = is_pipe(lst_token);
	if (pipe)
	{
		exec_with_pipe(lst_token, shell, fd_in, fd_out);
	}
	else
	{
		if (is_builtin(lst_token))
			builtin_cmd(lst_token, shell, fd_out);
		else
			non_builtin_cmd(lst_token, shell, fd_in, fd_out);
	}
}
