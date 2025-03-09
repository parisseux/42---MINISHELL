#include "../inc/minishell.h"

//attention on n/'a pas le droit a la fonction fprintf??? 
// il faut utiliser write(STDOUT_FILENO, ...)
void	printf_or_fprintf(t_file *file, char **line)
{
	if (file != NULL)
		fprintf(file->file, "%c", **line);
	else
		printf("%c", **line);
}
