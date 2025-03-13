#include "../inc/minishell.h"

void prep_var_shell(char ***var)
{
    if (var == NULL)
        return;
    *var = (char **)malloc(sizeof(char *) * 2);
    if (!*var) 
        return;
    (*var)[0] = ft_strdup(""); 
    if (!(*var)[0]) {
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
        if (ft_strchr(tmp->value, '=') && tmp->type == WORD && tmp->type != DQUOTE)
        {
            if (good_varname(tmp->value))
                return ;
            if (!add_var_to_env(shell->var_env, tmp->value, 1))
            {
                if (shell->shell_env == NULL)
                    prep_var_shell(&shell->shell_env);
                (add_var_to_env(shell->shell_env, tmp->value, 0));
            }
        }
        tmp = tmp->next;
    }
}
