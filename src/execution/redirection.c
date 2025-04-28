#include "../inc/minishell.h"

int	look_for_fd_heredoc(t_token *token, int fd, t_shell *shell)
{
	int	pipefd[2];
	int	pid;
	int	status;

	status = 0;
	if (pipe(pipefd) == -1)
		return (perror("pipe"), shell->exit = 1, -1);
	pid = fork();
	if (pid == 0)
		heredoc_child(pipefd[1], token, shell);
	if (heredoc_parent(pipefd, &status, pid, shell) == -1)
		return (-2);
	if (fd != -1)
		close(fd);
	return (pipefd[0]);
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
	int		fd_in;
	int		fd_out;

	fd_in = -1;
	fd_out = -1;
	temp = lst_token;
	while (temp->type != END && temp->type != PIPE)
	{
		if (temp->type == REDIR_OUT)
			fd_out = look_for_fd_output(temp->next, fd_out, shell);
		else if (temp->type == APPEND)
			fd_out = look_for_fd_append(temp->next, fd_out, shell);
		else if (temp->type == HEREDOC)
		{
			fd_in = look_for_fd_heredoc(temp->next, fd_in, shell);
			if (fd_in == -2)
				return (1);
		}
		else if (temp->type == REDIR_IN)
			fd_in = look_for_fd_input(temp->next, fd_in, shell);
		temp = temp->next;
	}
	change_fd(fd_out, fd_in);
	return (0);
}
