#include "../inc/minishell.h"

void	look_for_fd_heredoc(t_token *token, int *fd)
{
	int		fd_pipe[2];
	char	*stop;
	int pid;

	if (pipe(fd_pipe) == -1)
	{
		perror("pipe");
		exit(1);
	}
	pid  = fork();
	if (pid < 0)
	{
		perror("fork");
		exit(1);
	}
	else if (pid  == 0)
	{
		restore_signals();
		close(fd_pipe[0]);
		stop = ft_strdup(token->value);
		handle_heredoc_prompt(fd_pipe[1], stop);
		free(stop);
		close(fd_pipe[1]);
		exit(0);
	}
	close(fd_pipe[1]);
	signal(SIGINT, SIG_IGN);
	waitpid(pid, NULL, 0);
	init_signals();
	*fd = fd_pipe[0];
}

void	look_for_fd_append(t_token *token, int *fd)
{
	if (*fd != -1)
		close(*fd);
	*fd = open(token->value, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (*fd == -1)
	{
		perror("open");
		exit(1);
	}
}

void	look_for_fd_output(t_token *token, int *fd)
{
	if (*fd != -1)
		close(*fd);
	*fd = open(token->value, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (*fd == -1)
	{
		perror("open");
		exit(1);
	}
}

//if < will recoer the fd and send it so the execve know
void	look_for_fd_input(t_token *token, int *fd)
{
	if (*fd != -1)
		close (*fd);
	*fd = open(token->value, O_RDONLY);
	if (*fd == -1)
	{
		perror("open");
		exit(1);
	}
}

//handle the redirection in the case of non builtin cmd
//look for the fd of the input and output
//file and send it to the function to eecute
void	handle_redir(t_token *lst_token, int *fd_in, int *fd_out)
{
	t_token	*temp;

	temp = lst_token;
	while (temp->type != END)
	{
		if (temp->type == REDIR_OUT)
			look_for_fd_output(temp->next, fd_out);
		else if (temp->type == APPEND)
			look_for_fd_append(temp->next, fd_out);
		else if (temp->type == HEREDOC)
			look_for_fd_heredoc(temp->next, fd_in);
		else if (temp->type == REDIR_IN)
			look_for_fd_input(temp->next, fd_in);
		temp = temp->next;
	}
}
