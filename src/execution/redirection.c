#include "../inc/minishell.h"

int	look_for_fd_heredoc(t_token *token, int fd, t_shell *shell)
{
	int		fd_pipe[2];
	char	*stop;
	int		pid;
	int		status;

	if (pipe(fd_pipe) == -1)
	{
		perror("pipe");
		return (1);
	}
	pid = fork();
	if (pid < 0)
	{
		perror("fork");
		return (1);
	}
	else if (pid == 0)
	{
		restore_signals();
		close(fd_pipe[0]);
		stop = ft_strdup(token->value);
		handle_heredoc_prompt(fd_pipe[1], stop, shell);
		free(stop);
		close(fd_pipe[1]);
		exit(0);
	}
	close(fd_pipe[1]);
	signal(SIGINT, SIG_IGN);
	waitpid(pid, &status, 0);
	extract_exit_status(status, shell);
	init_signals();
	if (fd != -1)
		close(fd);
	fd = fd_pipe[0];
	return (fd);
}

int	look_for_fd_append(t_token *token, int fd, t_shell *shell)
{
	if (fd != -1)
		close(fd);
	fd = open(token->value, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd == -1)
	{
		perror("open");
		shell->exit = 1;
		return (1);
	}
	return (fd);
}

int	look_for_fd_output(t_token *token, int fd, t_shell *shell)
{
	if (fd != -1)
		close(fd);
	fd = open(token->value, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
	{
		perror("open");
		shell->exit = 1;
		return (1);
	}
	return (fd);
}

//if < will recoer the fd and send it so the execve know
int	look_for_fd_input(t_token *token, int fd, t_shell *shell)
{
	if (fd != -1)
		close(fd);
	fd = open(token->value, O_RDONLY);
	if (fd == -1)
	{
		perror("open");
		shell->exit = 1;
		return (1);
	}
	return (fd);
}

int	handle_redir(t_token *lst_token, t_shell *shell)
{
	t_token	*temp;
	int	fd_in;
	int	fd_out;

	fd_in = -1;
	fd_out = -1;
	temp = lst_token;
	while (temp->type != END && temp->type != PIPE)
	{
		if (temp->type == REDIR_OUT)
			fd_out = look_for_fd_output(temp->next, fd_out, shell);
		else if (temp->type == APPEND)
			fd_out =look_for_fd_append(temp->next, fd_out, shell);
		else if (temp->type == HEREDOC)
			fd_in = look_for_fd_heredoc(temp->next, fd_in, shell);
		else if (temp->type == REDIR_IN)
			fd_in = look_for_fd_input(temp->next, fd_in, shell);
		temp = temp->next;
	}
	change_fd(fd_out, fd_in);
	return (0);
}
