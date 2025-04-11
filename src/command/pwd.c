#include "../inc/minishell.h"

//exit status grace a waitpid

int	pwd_command(void)
{
	char	*pwd;

	pwd = NULL;
	pwd = getcwd(pwd, 0);
	if (!pwd)
		return (perror("malloc"), 1);
	write(STDOUT_FILENO, pwd, ft_strlen(pwd));
	write(STDOUT_FILENO, "\n", 1);
	free(pwd);
	return (1);
}
