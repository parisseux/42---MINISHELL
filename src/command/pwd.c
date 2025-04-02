#include "../inc/minishell.h"

//exit status grace a waitpid

void	pwd_command(void)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	write(STDOUT_FILENO, pwd, ft_strlen(pwd));
	write(STDOUT_FILENO, "\n", 1);
	free(pwd);
}
