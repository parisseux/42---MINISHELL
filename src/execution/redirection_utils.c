#include "../inc/minishell.h"

//introduire expansion variable
//doit introduire plusieurs HEREDOC succesif 
void	handle_heredoc_prompt(int fd_write, char *stop, t_shell *shell)
{
	char	*line;

	restore_signals();
	signals_heredoc();
	while (1)
	{
		line = readline("> ");
		if (!line)
		{
			ft_putstr_fd("warning: here-document delimited by EOF\n", 2);
			shell->exit = 0;
			break ;
		}
		if (!line || !ft_strncmp(line, stop, ft_strlen(stop) + 1))
		{
			free (line);
			break ;
		}
		write(fd_write, line, ft_strlen(line));
		write(fd_write, "\n", 1);
		free(line);
	}
	close(fd_write);
	init_signals();
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
