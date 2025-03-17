#include "../inc/minishell.h"

//introduire expansion variable
//doit introduire plusieurs HEREDOC succesif 
void	handle_heredoc_prompt( int fd_write, char *stop)
{
	char	*line;
	
	restore_signals();
	signals_heredoc();
	while (1)
	{
		line = readline("> ");
		if (!line)
		{
			write(STDOUT_FILENO, "warning: here-document delimited by EOF\n", 40);
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
