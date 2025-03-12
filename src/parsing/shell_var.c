#include "../inc/minishell.h"

#include <stdio.h>

void print_array(char **array)
{
    int i = 0;
    while (array[i] != NULL)
    {
        printf("%s\n", array[i]);
        i++;
    }
}

void prep_var_shell(char ***var)
{
    if (var == NULL) {
        fprintf(stderr, "Error: var is NULL\n");
        return;
    }
    *var = (char **)malloc(sizeof(char *) * 2);
    if (!*var) {
        fprintf(stderr, "Error: memory allocation failed\n");
        return;
    }

    (*var)[0] = strdup(""); 
    if (!(*var)[0]) {
        fprintf(stderr, "Error: memory allocation failed for var[0]\n");
        free(*var);
        return;
    }
    (*var)[1] = NULL; 
}



void    shell_var(t_token *lst_token, t_shell *shell)
{
    t_token *tmp;

    tmp = lst_token;
    if (is_pipe(lst_token))
        return ;
    while (tmp->type != END)
    {
        if (ft_strchr(tmp->value, '=') && tmp->type == WORD)
        {
            if (good_varname(tmp->value))
                return ;
            if (!add_var_to_env(shell->var_env, tmp->value, 1))
            {
                write(1, "not in env\n", 12);
                if (shell->shell_env == NULL)
                    prep_var_shell(&shell->shell_env);
                (add_var_to_env(shell->shell_env, tmp->value, 0));
            }
        }
        tmp = tmp->next;
    }
    print_array(shell->shell_env);
}
