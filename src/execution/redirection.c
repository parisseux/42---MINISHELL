#include "../inc/minishell.h"

// void handle_hereodc_fd(t_token *lst_token, int *fd_in)
// {
// 	t_token *temp;

// }
//fd[0] ==> on lit
// fd[1] ==> on ecrit
int	look_for_fd_heredoc(t_token *lst_token)
{
	int fd[2];
	char *line;
	t_token *temp;
	char *stop;

	temp = lst_token;
	line = NULL;
	while (temp && temp->type != END)
	{
		if (temp->type == HEREDOC && temp->next)
		{
			if (pipe(fd) == -1)
				return (-1);
			stop = temp->next->value;
			while (1)
			{
				line = readline("> ");
				if (!line || !ft_strncmp(line, stop, ft_strlen(stop) + 1))
					break ;
				write(fd[1], line, ft_strlen(line));
				write(fd[1], "\n", 1);
				free(line);
			}
			if (line)
				free(line);
			close(fd[1]);
			return (fd[0]);
		}
		temp = temp->next;
	}
	return (-1);
}
//if > or >> will go through them to check whats the last file and
// so where the output need to be
int	look_for_fd_output(t_token *lst_token)
{
	int		fd;
	t_token	*temp;

	fd = -1;
	temp = lst_token;
	while (temp->type != END)
	{
		if (temp->type == REDIR_OUT)
		{
			if (fd != -1)
				close(fd);
			fd = open(temp->next->value, O_WRONLY | O_CREAT | O_TRUNC, 0644);
			if (fd == -1)
			{
				perror("open");
				exit(1);
			}
		}
		else if (temp->type == APPEND)
		{
			if (fd != -1)
				close(fd);
			fd = open(temp->next->value, O_WRONLY | O_CREAT | O_APPEND, 0644);
			if (fd == -1)
			{
				perror("open");
				exit(1);
			}
		}
		temp = temp->next;
	}
	return (fd);
}

//if < will recoer the fd and send it so the execve know
int	look_for_fd_input(t_token *lst_token)
{
	int		fd;
	t_token	*temp;

	fd = -1;
	temp = lst_token;
	while (temp->type != END)
	{
		if (temp->type == REDIR_IN)
		{
			if (fd != -1)
				close (fd);
			fd = open(temp->next->value, O_RDONLY);
			if (fd == -1)
			{
				perror("open");
				exit(1);
			}
		}
		temp = temp->next;
	}
	return (fd);
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
		if (temp->type == REDIR_OUT || temp->type == APPEND)
			*fd_out = look_for_fd_output(lst_token);
		else if (temp->type == HEREDOC)
			*fd_in = look_for_fd_heredoc(lst_token);
		else if (temp->type == REDIR_IN)
			*fd_in = look_for_fd_input(lst_token);
		temp = temp->next;
	}
}
