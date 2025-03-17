#include "../inc/minishell.h"

int detect_var(char *input)
{
    int len;
    int check;

    len = 0;
    check = 0;
    while (*input != ' ' && *input!= '\0')
    {
        if (*input == '=')
            check = 1;
        len++;
        input++;
    }
    if (check)
        return (1);
    return (0);
}

t_token *token_var(char **input)
{
    t_token *new_token;
    char    *copy;
    int     len;
    int     check;

    len = 0;
    check = 0;
    copy = *input;
    while (**input != ' ' && **input!= '\0')
    {
        if (**input == '=')
            check = 1;
        len++;
        (*input)++;
    }
    if (check)
    {
        copy[len] = '\0';
        new_token = create_token(copy, DEF);
    }
    if (!new_token)
        return (NULL);
    return (new_token);    
}
