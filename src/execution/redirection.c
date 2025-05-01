#include "../inc/minishell.h"

int prepare_heredocs(t_token *lst, t_shell *shell)
{
	t_token	*temp;
	int		fd;

	temp = lst;
	fd = -1;
	while (temp->type != END)
	{
		if (temp->type == HEREDOC)
		{
			if (build_heredoc(temp->next, &fd, shell) == -1)
				return (-1);
			temp->fd_hd = fd;
		}
		fd = -1;
		temp = temp->next;
	}
	return (0);
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
	if (access(token->value, R_OK) == -1)
	{
		perror(token->value);
		shell->exit = 1;
		return (-1);
	}
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
			if (fd_in != -1)
				close(fd_in);
			fd_in = temp->fd_hd;
		} 	
		else if (temp->type == REDIR_IN)
			fd_in = look_for_fd_input(temp->next, fd_in, shell);
		temp = temp->next;
	}
	change_fd(fd_out, fd_in);
	return (0);
}
