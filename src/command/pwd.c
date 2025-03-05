#include "../inc/minishell.h"

void	pwd_command(t_file *file)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	if (file)
		fprintf(file->file, "%s\n", pwd);
	else
		printf("%s\n", pwd);
	free(pwd);
}
