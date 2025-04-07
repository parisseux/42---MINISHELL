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

void	close_all_pipes_except(int pipefd[][2], int i, int n_pipes)
{
	int	j;

	j = 0;
	while (j < n_pipes)
	{
		if (j != i && j != i - 1)
		{
			close(pipefd[j][0]);
			close(pipefd[j][1]);
		}
		j++;
	}
}