#include "../inc/minishell.h"

void    printf_or_fprintf(t_file *file, char **line)
{
    if (file != NULL)
		fprintf(file->file, "%c", **line);
	else
		printf("%c", **line);
}
