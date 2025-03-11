#include "../inc/minishell.h"

void	cd_command(t_token *lst_token, t_shell *shell)
{
	char	*home;
	char	*path;

	path = NULL;
	if (lst_token && (lst_token->type == WORD || lst_token->type == SQUOTE
			|| lst_token->type == DQUOTE))
		path = lst_token->value;
	if (!path)
	{
		home = get_env_value(shell->var_env, "HOME");
		if (!home)
		{
			write(STDERR_FILENO, "cd: HOME not set\n", 17);
			return ;
		}
		path = home;
	}
	if (chdir(path) == -1)
	{
		write(STDERR_FILENO, "cd: ", 4);
		write(STDERR_FILENO, path, ft_strlen(path));
		write(STDERR_FILENO, ": No such file or directory\n", 28);
	}
}
