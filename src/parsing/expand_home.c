#include "../inc/minishell.h"

char	*ft_strncpy(char *dest, const char *src, size_t size)
{
	size_t	i;

	i = ft_strlen(src);
	if (i + 1 < size)
	{
        while (*src && i != 0)
        {
            *dest++ = *src++;
            i--;
        }
        *dest = '\0';
    }
	else if (size != 0)
	{
		while (*src && size > 1)
        {
            *dest++ = *src++;
            size--;
        }
        *dest = '\0';
    }
    write (1, dest, ft_strlen(dest));
    write (1, "\n", 1);
	return (dest);
}

char    *replace_home(char *str, t_shell *shell, int i)
{
    char    *new_str;
    char    *tmp;

    write (1, "in replace_home\n", 17);
    new_str = (char *)malloc(sizeof(char) * (ft_strlen(str) + ft_strlen(get_env_value(shell->var_env, "HOME"))));
    if (!new_str)
        return (NULL);
    new_str = ft_strncpy(new_str, str, i);
    tmp = ft_strjoin(new_str, get_env_value(shell->var_env, "HOME"));
    if (!tmp)
    {
        free(new_str);
        return (NULL);
    }
    new_str = ft_strjoin(tmp, str + i + 1);
    if (!new_str)
    {
        free(tmp);
        return (NULL);
    }
    return (new_str);
}

void    expand_home(t_shell *shell, t_token *lst_token)
{
    int i;
    char *home;

    i = 0;
    while (lst_token->type != END)
    {
        if (lst_token->type == WORD || lst_token->type == DQUOTE)
        {
            while (lst_token->value[i] != '\0')
            {
                if (lst_token->value[i] == '~')
                {
                    write (1, "found\n", 7);
                    home = get_env_value(shell->var_env, "HOME");
                    if (!home)
                    {
                        write(STDOUT_FILENO, "cd: HOME not set\n", 17);
                        shell->exit = 1;
                        return ;
                    }
                    else
                        write(STDOUT_FILENO, "HOME is set\n", 12);
                    free(lst_token->value);
                    lst_token->value = replace_home(lst_token->value, shell, i);
                    i = 0;
                }
                else
                    i++;
            }
        }
        lst_token = lst_token->next;
    }
}

