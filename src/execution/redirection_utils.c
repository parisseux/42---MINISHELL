#include "../inc/minishell.h"

int heredoc_parent(int *pipefd, int *status, int pid)
{
	close(pipefd[1]);
	signal(SIGINT, SIG_IGN);
	waitpid(pid, status, 0);
	signal(SIGINT, sigint_handler);
	if (WEXITSTATUS(*status) == 130)
	{
		close(pipefd[0]);
		return (-1);
	}
	return (0);
}
void heredoc_child(int *pipefd, t_token *lst_token)
{
	char *stop;
	char *line;

	signal(SIGINT, sigint_handler_heredoc);
	signal(SIGQUIT, SIG_IGN);
	stop = ft_strdup(lst_token->value);
	while (1)
	{
		line = readline("> ");
		if (!line)
			break ;
		if (ft_strncmp(line, stop, ft_strlen(stop) + 1) == 0)
		{
			free(line);
			break ;
		}
		line = ft_strjoin(line, "\n");
		ft_putstr_fd(line, pipefd[1]);
		free(line);
	}
	free(stop);
	close(pipefd[0]);
	close(pipefd[1]);
	exit(0);
}

void	change_fd(int fd_out, int fd_in)
{
	if (fd_out != -1)
	{
		dup2(fd_out, STDOUT_FILENO);
		close(fd_out);
	}
	if (fd_in != -1)
	{
		dup2(fd_in, STDIN_FILENO);
		close (fd_in);
	}
}
