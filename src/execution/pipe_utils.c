#include "../inc/minishell.h"

void close_all_pipes(int pipefd[][2], int n_pipes)
{
    int i;

    i = 0;
	while (i < n_pipes)
	{
		close(pipefd[i][0]);
		close(pipefd[i][1]);
		i++;
	}

}

void wait_all_pids(int *pids, int *status,  int n_cmd)
{
    int i;

    i = 0;
	while (i < n_cmd)
	{
		waitpid(pids[i], status, 0);
		i++;
	}
}

void create_all_pipes(int pipefd[][2], int n_pipes)
{
    int i;

    i = 0;
    while (i < n_pipes)
        {
            if (pipe(pipefd[i]) == -1)
                return (perror("pipe"));
            i++;
        }
}
