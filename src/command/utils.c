#include "../inc/minishell.h"

void    printf_or_fprintf(t_file *file, char **line)
{
    if (file != NULL)
		fprintf(file->file, "%c", **line);
	else
		printf("%c", **line);
}

int is_pipe(t_token *lst_token)
{
    int pipe;
    t_token *temp;

    pipe = 0;
    temp = lst_token;
    while (temp->type != END)
    {
        if (temp->type == PIPE)
            pipe++;
        temp = temp->next;
    }
    return (pipe);
}

int is_builtin(t_token *lst_token)
{
    t_token *temp;

    temp = lst_token;
    while (temp->type != WORD)
        temp = temp->next;
    if (!ft_strncmp(temp->value, "echo", 5))
        return (1);
    else if (!ft_strncmp(temp->value, "cd", 3))
        return (1);
    else if (!ft_strncmp(temp->value, "pwd", 4))
        return (1);
    else if (!ft_strncmp(temp->value, "export", 7))
        return (1);
    else if (!ft_strncmp(temp->value, "unset", 5))
        return (1);
    else if (!ft_strncmp(temp->value, "env", 4))
        return (1);
    else if (!ft_strncmp(temp->value, "exit", 6))
        return (1);
    else 
        return (0);
}
