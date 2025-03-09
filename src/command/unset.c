#include "../inc/minishell.h"

void	unset_command(char *line, t_shell *shell)
{
	int	i;

	i = 0;
	while (shell->var_env[i])
	{
		if (!ft_varcmp(shell->var_env[i], line, ft_strlen(line)))
		{
			free(shell->var_env[i]);
			while (shell->var_env[i])
			{
				shell->var_env[i] = shell->var_env[i + 1];
				i++;
			}
			return ;
		}
		i++;
	}
}
