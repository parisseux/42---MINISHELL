#include "../inc/minishell.h"

void	export_message_error(char *value, t_shell *shell)
{
	if (!ft_strncmp(value, "-", 1))
	{
		write(STDERR_FILENO, "minishell: export: -", 20);
		write(STDERR_FILENO, &value[1], 1);
		write(STDERR_FILENO, ": invalid option\n", 17);
		write(STDERR_FILENO, "export: usage: export [-fn]", 17);
		write(STDERR_FILENO, " [name[=value] ...] or export -p\n", 33);
		shell->exit = 2;
	}
	else
	{
		write(STDERR_FILENO, "minishell: export: `", 20);
		write(STDERR_FILENO, value, ft_strlen(value));
		write(STDERR_FILENO, "': not a valid identifier\n", 26);
		shell->exit = 1;
	}
}
