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

void	shell_var(t_token *lst_token, t_shell *shell)
{
	t_token	*tmp;
	char	**tab;

	tmp = lst_token;
	if (is_pipe(lst_token))
		return ;
	while (tmp->type != END)
	{
		if (tmp->type == DEF)
		{
			if (good_varname(tmp->value, '='))
				return ;
			if (add_var_to_env(shell->var_env, tmp->value, 1) == NULL)
			{
				if (shell->shell_env == NULL)
					prep_var_shell(&shell->shell_env);
				tab = add_var_to_env(shell->shell_env, tmp->value, 0);
				shell->shell_env = tab;
			}
		}
		tmp = tmp->next;
	}
}
