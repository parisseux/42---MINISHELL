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
			write(STDOUT_FILENO, "cd: HOME not set\n", 17);
			shell->exit = 1;
			return ;
		}
		path = home;
	}
	if (chdir(path) == -1)
	{
		write(STDOUT_FILENO, "cd: ", 4);
		write(STDOUT_FILENO, path, ft_strlen(path));
		write(STDOUT_FILENO, ": No such file or directory\n", 28);
		shell->exit = 2;
	}
}
