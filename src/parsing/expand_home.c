#include "../inc/minishell.h"

void	expand_home(t_shell *shell, t_token *lst_token)
{
	int		i;
	char	*home;
	char	*tmp;

	i = 0;
	while (lst_token->type != END)
	{
		if (lst_token->type == WORD || lst_token->type == DQUOTE)
		{
			tmp = ft_strdup(lst_token->value);
			i = 0;
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
					lst_token->value = add(home, tmp, 1, '~');
					tmp = ft_strdup(lst_token->value);
					i = 0;
				}
				else
					i++;
			}
		}
		lst_token = lst_token->next;
	}
}
