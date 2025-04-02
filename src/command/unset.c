#include "../inc/minishell.h"

int	invalid_option(char *line, t_shell *shell)
{
	if (!ft_strncmp(line, "-", 1))
	{
		write(STDOUT_FILENO, "minishell: unset: -", 20);
		write(STDOUT_FILENO, &line[1], 1);
		write(STDOUT_FILENO, ": invalid option\n", 17);
		write(STDOUT_FILENO, "export: usage: export [-fn] [name[=value] ...] or export -p\n", 60);
		shell->exit = 2;
		return (1);
	}
	return (0);
}

void	unset_command(char *line, t_shell *shell)
{
	int	i;

	i = 0;
	if (invalid_option(line, shell))
		return ;
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
	i = 0;
	if (shell->shell_env != NULL)
	{
		while (shell->shell_env[i])
		{
			if (!ft_varcmp(shell->shell_env[i], line, ft_strlen(line)))
			{
				free(shell->shell_env[i]);
				while (shell->shell_env[i])
				{
					shell->shell_env[i] = shell->shell_env[i + 1];
					i++;
				}
				return ;
			}
			i++;
		}
	}
}
