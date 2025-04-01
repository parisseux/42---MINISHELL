#include "../inc/minishell.h"

int not_cmd(t_token *lst_token) // ajouter tout le reste ?
{
    t_token *tmp;

    tmp = lst_token;
    if (lst_token == NULL)
        return (0);
    if (!ft_strncmp(tmp->value, "echo", 4))
        return (1);
    else if (!ft_strncmp(tmp->value, "cd", 3))
		return (1);
	else if (!ft_strncmp(tmp->value, "pwd", 4))
		return (1);
	else if (!ft_strncmp(tmp->value, "unset", 5))
		return (1);
	else if (!ft_strncmp(tmp->value, "env", 4))
		return (1);
	else if (!ft_strncmp(tmp->value, "exit", 6))
		return (1);
    else if (!ft_strncmp(tmp->value, "ls", 3))
		return (1);
	else if (!ft_strncmp(tmp->value, "cat", 4))
		return (1);
    return (0);
}
