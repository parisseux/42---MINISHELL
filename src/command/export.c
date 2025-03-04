#include "../inc/minishell.h"

// a revoir
void    print_export(t_shell *shell)
{
    int i;

    i = 0;
    while (shell->var_env[i])
    {
        printf("declare -x %s\n", shell->var_env[i]);
        i++;
    }
}

// add a la fin pas exactement pareil mais bon ...
void    add_var_to_env(char **var_env, char *value)
{
    int i;
    int j;
    int check;

    i = 0;
    j = 0;
    check = 0;
    while (value[j] != '=')
        j++;
    while (var_env[i] != NULL)
    {
        if (!ft_varcmp(var_env[i], value, j))
        {
            free(var_env[i]);
            var_env[i] = ft_strdup(value);
            check = 1;
            return ;
        }
        i++;
    }
    if (!check)
    {
        var_env[i] = ft_strdup(value);
        var_env[i + 1] = NULL;        
    }
}

int good_varname(char *name)
{
    int i;

    i = 0;
    while (name[i] != '=')
    {
        if (!ft_isalnum(name[i]) && name[i] != '_')
            return (1);
        i++;
    }
    if (i == 0)
        return (1);
    return (0);
}

void    export_command(t_token *lst_token, t_shell *shell)
{
    t_token *tmp;

    tmp = lst_token->next;
    if (tmp->type == END)
    {
        print_export(shell);
        return ;
    }
    while (tmp->type != END)
    {
        if (ft_strchr(tmp->value, '='))
        {
            if (good_varname(tmp->value))
            {
                printf("minishell: export: `%s': not a valid identifier\n", tmp->value);
                g_exit_status = 1;
                return ;
            }
            else
                add_var_to_env(shell->var_env, tmp->value);
        }
        else
            g_exit_status = 1;
        tmp = tmp->next;
    }
}
