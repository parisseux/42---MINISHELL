#include "../inc/minishell.h"


//doit introduire plusieurs HEREDOC succesif 
void	handle_heredoc_prompt(t_token *lst_token, int fd_write)
{
	char *stop;
	char *line;
	t_token *temp;

	temp = lst_token;
	stop = temp->next->value;
	while (1)
	{
		line = readline("> ");
		if (!line || !ft_strncmp(line, stop, ft_strlen(stop) + 1))
			break ;
		write(fd_write, line, ft_strlen(line));
		write(fd_write, "\n", 1);
		free(line);
	}
	if (line)
		free(line);
	close(fd_write);
}

int	look_for_fd_heredoc(t_token *lst_token)
{
	int fd[2];
	t_token *temp;


	temp = lst_token;
	while (temp && temp->type != END)
	{
		if (temp->type == HEREDOC && temp->next)
		{
			if (pipe(fd) == -1)
				return (-1);
			handle_heredoc_prompt(temp, fd[1]);
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
