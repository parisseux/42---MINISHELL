#include "../inc/minishell.h"

void    expand_home(t_shell *shell, t_token *lst_token)
{
    int i;
    char *home;
    char *tmp;
    char    *new;

    i = 0;
    home = get_env_value(shell->var_env, "HOME");
    if (!home)
    {
        write(STDOUT_FILENO, "cd: HOME not set\n", 17);
        shell->exit = 1;
        return ;
    }
    while (lst_token->type != END)
    {
        if (lst_token->type == WORD || lst_token->type == DQUOTE)
        {
            tmp = ft_strdup(lst_token->value);
            i = 0;
            while (tmp[i] != '\0')
            {
                if (tmp[i] == '~')
                {
                    new = add(home, tmp, 0, '~');
                    free(lst_token->value);
                    lst_token->value = new;
                    tmp = ft_strdup(lst_token->value);
                    i = 0;
                }
                else
                    i++;
            }
            free(tmp);
        }
        lst_token = lst_token->next;
    }
}

