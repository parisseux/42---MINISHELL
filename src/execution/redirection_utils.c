#include "../inc/minishell.h"

int	heredoc_parent(int pipefd, int pid, t_shell *shell)
{
	struct sigaction	old_int;
	struct sigaction	old_quit;
	struct sigaction	sa_ignore;
	int					status;

	sa_ignore.sa_handler = SIG_IGN;
	sigemptyset(&sa_ignore.sa_mask);
	sa_ignore.sa_flags = 0;
	sigaction(SIGINT, &sa_ignore, &old_int);
	sigaction(SIGQUIT, &sa_ignore, &old_quit);
	waitpid(pid, &status, 0);
	sigaction(SIGINT, &old_int, NULL);
	sigaction(SIGQUIT, &old_quit, NULL);
	if (WIFSIGNALED(status))
	{
		shell->exit = 128 + WTERMSIG(status);
		close(pipefd);
		return (-1);
	}
	if (WIFEXITED(status) && WEXITSTATUS(status) == 130)
	{
		shell->exit = 128 + WTERMSIG(status);
		close(pipefd);
		printf("exit status: %d\n", shell->exit);
		return (-1);
	}
	shell->exit = WEXITSTATUS(status);
	printf("exit status: %d\n", shell->exit);
	return (0);
}

void	heredoc_child(int pipefd, t_token *lst_token, t_shell *shell)
{
	char	*stop;
	char	*line;

	//setpgid(0, 0);
	init_heredoc_child_signals();
	stop = ft_strdup(lst_token->value);
	while (1)
	{
		line = readline("> ");
		if (!line)
			break ;
		if (lst_token->type == WORD && isvalid(0, line) == 1)
			which(&line, shell);
		if (ft_strncmp(line, stop, ft_strlen(stop) + 1) == 0)
		{
			free(line);
			break ;
		}
		ft_putstr_fd(line, pipefd);
		ft_putchar_fd('\n', pipefd);
		free(line);
	}
	free(stop);
	close(pipefd);
	cleanup_readline();
	exit(shell->exit);
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

void close_heredoc(t_token *lst)
{
	t_token *t;

	t = lst;
	while (t->type != END)
	{
		if (t->type == HEREDOC && t->fd_hd != -1)
			close(t->fd_hd);
		t = t->next;
	}
}

int build_heredoc(t_token *lst, int *fd, t_shell  *shell)
{
	int pipefd[2];
	int pid;

	if (pipe(pipefd) == -1)
		return(perror("pipe"), -1);
	pid = fork();
	if (pid == -1)
		return(perror("fork"), close(pipefd[0]), close(pipefd[1]), -1);
	if (pid == 0)
	{
		close(pipefd[0]);
		heredoc_child(pipefd[1], lst, shell);
	}
	close(pipefd[1]);
	heredoc_parent(pipefd[0], pid, shell);
	*fd = pipefd[0];
    return (0);

}
