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
