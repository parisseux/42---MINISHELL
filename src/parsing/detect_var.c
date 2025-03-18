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

int closed_quotes(char *copy, char quote, int i)
{
    int     len;

    len = 0;
    i++;
    while (copy[i] != '\0')
    {
        if (copy[i] == quote)
            return (len);
        i++;
        len++;
    }
    return (-1);
}

char *rm_quotes(char *input)
{
    char    *cleaned;
    int     size;
    int     i;
    int     j;

    i = 0;
    size = 0;
    j = 0;
    if (!ft_strchr(input, '\'') && !ft_strchr(input, '"'))
        return (input);
    cleaned = ft_strdup("");
    while (input[i] != '\0')
    {
        if (input[i] == '\'' || input[i] == '"')
        {
            size = closed_quotes(input, input[i], i);
            if (size == -1)
            {
                free(cleaned);
                return (NULL);
            }
            i++;
            while (size > 0)
            {
                cleaned[j] = input[i];
                j++;
                i++;
                size--;
            }
            i++;
        }
        else
            cleaned[j++] = input[i++];

    }
    cleaned[j] = '\0';
    return (cleaned);
}

t_token *token_var(char **input)
{
    t_token *new_token;
    char    *copy;
    char    *new;
    int     len;

    len = 0;
    new = NULL;
    copy = ft_strdup(*input);
    while (**input != ' ' && !ft_strchr("|<>", **input) && **input!= '\0')
    {
        len++;
        (*input)++;
    }
    copy[len] = '\0';
    new = rm_quotes(copy);
    if (!new)
        new_token = NULL;
    else
        new_token = create_token(new, DEF);
    free(copy);
    new = NULL;
    if (!new_token)
        return (NULL);
    return (new_token);    
}
