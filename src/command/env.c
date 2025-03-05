#include "../inc/minishell.h"

void	env_command(t_shell *shell, t_token *lst_token, t_file *file)
{
	char	**var_env;

	var_env = shell->var_env;
	int i;
	i = 0;
	if (lst_token->next->type == 8 || lst_token->next->type == APPEND || lst_token->next->type == REDIR_OUT)
	{
		while (var_env[i])
		{
			if (file != NULL)
			{
				fprintf(file->file, "%s\n", var_env[i]);
				i++;
			}
			else
			{
				printf("%s\n", var_env[i]);
				i++;    
			}
		}
	}
	else
		printf("env: %s: No such file or directory\n", lst_token->next->value);
}
