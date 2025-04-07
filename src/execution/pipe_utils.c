#include "../inc/minishell.h"

void	close_all_pipes(int pipefd[][2], int n_pipes)
{
	int	i;

	i = 0;
	while (i < n_pipes)
	{
		close(pipefd[i][0]);
		close(pipefd[i][1]);
		i++;
	}

}

void close_all_pipes_except(int pipefd[][2], int i, int n_pipes)
{
	int j;

	j = 0;
	while (j < n_pipes)
	{
		if (j!= i && j != i-1)
		{
			close(pipefd[j][0]);
			close(pipefd[j][1]);
		}
		j++;
	}
}

void	wait_all_pids(int *pids, t_shell *shell,  int n_cmd)
{
	int	i;
	int status;

	i = 0;
	status = 0;
	while (i < n_cmd)
	{
		if (i == n_cmd - 1)
		{
			waitpid(pids[i], &status, 0);
			extract_exit_status(status, shell);
		}
		else 
			waitpid(pids[i], &status,0 );
		i++;
	}
}

void	create_all_pipes(int pipefd[][2], int n_pipes)
{
	int	i;

	i = 0;
	while (i < n_pipes)
		{
			if (pipe(pipefd[i]) == -1)
				return (perror("pipe"));
			i++;
		}
}

void	go_to_next_pipe(t_token **lst_token)
{

	if (!lst_token || !*lst_token)
		return;
	while (*lst_token && (*lst_token)->type != PIPE && (*lst_token)->type != END)
		*lst_token = (*lst_token)->next;

	if (*lst_token && (*lst_token)->type == PIPE)
		*lst_token = (*lst_token)->next;
}
