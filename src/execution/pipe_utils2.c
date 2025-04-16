#include "../inc/minishell.h"

void	close_all_pipe(t_pipe *p)
{
	int	i;

	i = 0;
	while (i < p->n_pipes)
	{
		close(p->pipefd[i][0]);
		close(p->pipefd[i][1]);
		i++;
	}
	i = 0;
	while (i < p->n_pipes + 1)
		free(p->pipefd[i++]);
	free(p->pipefd);
}

void	close_all_pipes_except(int **pipefd, int i, int n_pipes)
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

void	free_cmds_lst(t_pipe *p)
{
	int	i;

	i = 0;
	while (i < p->n_pipes + 1)
	{
		free_token_list(p->cmds[i]);
		i++;
	}
}

void	create_pipe_and_mini_lst(t_pipe *p, t_token *lst_token)
{
	int	i;

	i = 0;
	while (i < p->n_pipes + 1)
	{
		p->cmds[i] = create_mini_list(&lst_token);
		i++;
	}
	p->cmds[i] = NULL;
	create_all_pipes(p->pipefd, p->n_pipes);
}

int	init_pipe_data(t_pipe *p, int n_pipes)
{
	int	i;

	ft_memset(p, 0, sizeof(*p));
	p->n_pipes = n_pipes;
	p->pids = malloc(sizeof(int) * (n_pipes + 1));
	if (!p->pids)
		return (1);
	p->cmds = malloc(sizeof(t_token *) * (n_pipes + 2));
	if (!p->cmds)
		return (1);
	p->pipefd = malloc(sizeof(int *) * (n_pipes + 1));
	if (!p->pipefd)
		return (1);
	i = 0;
	while (i < n_pipes + 1)
	{
		p->pipefd[i] = malloc(sizeof(int) * 2);
		if (!p->pipefd[i])
			return (1);
		i++;
	}
	return (0);
}
