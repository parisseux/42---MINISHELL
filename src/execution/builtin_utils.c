#include "../inc/minishell.h"

//ici il faut gerer: cd, export, unset and exit
void	builtin_parent_process(t_token *lst_token,
	t_shell *shell, int fd_out)
{
	t_token	*temp;

	temp = lst_token;
	while (temp->type != END)
	{
		if (temp->type == WORD || temp->type == DEF)
		{
			if (!ft_strncmp(temp->value, "cd", 3))
			{
				cd_command(temp->next, shell);
				break ;
			}
			else if (!ft_strncmp(temp->value, "export", 7))
			{
				export_command(temp, shell, fd_out);
				break ;
			}
			else if (!ft_strncmp(temp->value, "unset", 6))
			{
				unset_command(temp->next->value, shell);
				break ;
			}
			else if (!ft_strncmp(temp->value, "exit", 5))
			{
				exit_command(lst_token, shell);
				break ;
			}	
		}
		temp = temp->next;
	}
}

//ici il faut gerer:echo, pwd, env
//creation d'un child process qui va executer les builtin
void	builtin_child_process(t_token *lst_token, t_shell *shell, int fd_out)
{
	int		pid;
	t_token	*temp;
	int status;

	pid = fork();
	if (pid == 0)
	{
		restore_signals();
		temp = lst_token;
		while (temp->type != END)
		{
			if (!ft_strncmp(temp->value, "env", 4))
			{
				env_command(shell, lst_token, fd_out);
				break ;
			}
			else if (!ft_strncmp(temp->value, "pwd", 4))
			{
				pwd_command(fd_out);
				break ;
			}
			else if (!ft_strncmp(lst_token->value, "echo", 5))
			{
				if (lst_token->next->type == END)
					write(STDOUT_FILENO, "\n", 1);
				else if (!ft_strncmp(lst_token->next->value, "-n", 2))
					echo_command(lst_token->next->next, 1, fd_out);
				else
					echo_command(lst_token->next, 0, fd_out);
				break ;
			}
			temp = temp->next;
		}
		exit(0);
	}
	else
	{
		waitpid(pid, &status, 0);
		extract_exit_status(status, shell);
	}
}
