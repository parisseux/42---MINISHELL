#include "../inc/minishell.h"

void	cd_command(char *line)
{
	int	i;

	i = 0;
	while (*line == ' ')
		line++;
	if (!*line)
	{
		i = chdir(getenv("HOME"));
		if (i == -1)
			printf("cd: HOME not set\n");
		return ;
	}
	i = chdir((const char *)line);
	if (i == -1)
		printf("cd: %s: No such file or directory\n", line);
}
