#include "../inc/minishell.h"

void	pwd_command(int fd_out)
{
	char	*pwd;
	int saved_stdout;

	saved_stdout = dup(STDOUT_FILENO);
	pwd = getcwd(NULL, 0);
	if (fd_out !=-1)
	{
		dup2(fd_out, STDOUT_FILENO);
		close(fd_out);
	}
	write(STDOUT_FILENO, pwd, ft_strlen(pwd));
	write(STDOUT_FILENO, "\n", 1);
	free(pwd);
	dup2(saved_stdout, STDOUT_FILENO);
	close(saved_stdout);
}
