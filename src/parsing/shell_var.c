#include "../inc/minishell.h"

void	prep_var_shell(char ***var)
{
	if (var == NULL)
		return ;
	*var = (char **)malloc(sizeof(char *) * 2);
	if (!*var)
		return ;
	(*var)[0] = ft_strdup("");
	if (!(*var)[0])
	{
		free(*var);
		return ;
	}
	(*var)[1] = NULL;
}

int	len_var(char *value)
{
	int i;

	i = 0;
	while (value[i] != '\0')
	{
		if (value[i] == '=')
			return (i);
		i++;
	}
	return (-1);
}

int	shell_var(t_token *lst_token, t_shell *shell)
{
	t_token	*tmp;
	char	**tab;

	tmp = lst_token;
	if (is_pipe(lst_token))
		return (0);
	while (tmp->type != END)
	{
		if (tmp->type == DEF)
		{
			if (good_varname(tmp->value, '='))
				return (0);
			if (found_in_tab(shell->var_env, tmp->value, len_var(tmp->value)))
			{
				if (shell->shell_env == NULL)
					prep_var_shell(&shell->shell_env);
				tab = add_var_to_env(shell->shell_env, tmp->value);
				shell->shell_env = tab;
			}
		}
		tmp = tmp->next;
	}
	return (0);
}
