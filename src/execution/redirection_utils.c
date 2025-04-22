#include "../inc/minishell.h"

int	heredoc_parent(int *pipefd, int *status, int pid)
{
	struct sigaction old_int;
    struct sigaction old_quit;
    struct sigaction sa_ignore;

	close(pipefd[1]);
	sa_ignore.sa_handler = SIG_IGN;
    sigemptyset(&sa_ignore.sa_mask);
    sa_ignore.sa_flags = 0;
    sigaction(SIGINT,  &sa_ignore, &old_int);
    sigaction(SIGQUIT, &sa_ignore, &old_quit);
	waitpid(pid, status, 0);
	sigaction(SIGINT,  &old_int,  NULL);
    sigaction(SIGQUIT, &old_quit, NULL);
	if (WEXITSTATUS(*status) == 130)
	{
		close(pipefd[0]);
		return (-1);
	}
	return (0);
}

void	heredoc_child(int *pipefd, t_token *lst_token)
{
	char	*stop;
	char	*line;

	init_heredoc_child_signals();
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
		ft_putstr_fd(line, pipefd[1]);
		ft_putchar_fd('\n', pipefd[1]);
		free(line);
	}
	free(stop);
	close(pipefd[0]);
	close(pipefd[1]);
	free_token_list(lst_token);
	cleanup_readline();
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
