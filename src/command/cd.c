#include "../inc/minishell.h"

int count_argument_cd(t_token *lst_token)
{
	int n;
	t_token *temp;

	n = 0;
	temp = lst_token;
	while (temp->type != END && temp->type != PIPE)
	{
		if (temp->type == REDIR_IN || temp->type == REDIR_OUT
			|| temp->type == APPEND || temp->type == HEREDOC)
			temp =  temp->next->next;
		else if (temp->type == WORD || temp->type == SQUOTE
			|| temp->type == DQUOTE || temp->type == BIN)
		{
			n++;
			temp = temp->next;
		}
		else
			temp = temp->next;
	}
	return (n);
}

int	cd_command(t_token *lst_token, t_shell *shell)
{
	char	*home;
	char	*path;

	path = NULL;
	if (count_argument_cd(lst_token) > 1)
	{
		write(STDERR_FILENO, "cd: too many arguments\n", 23);
		return (1);
	}
	if (lst_token && (lst_token->type == WORD || lst_token->type == SQUOTE
			|| lst_token->type == DQUOTE || lst_token->type == BIN))
		path = lst_token->value;
	if (!path)
	{
		home = get_env_value(shell->var_env, "HOME");
		if (!home)
		{
			write(STDERR_FILENO, "cd: HOME not set\n", 17);
			return (1);
		}
		path = home;
	}
	if (chdir(path) == -1)
	{
		write(STDERR_FILENO, "cd: ", 4);
		write(STDERR_FILENO, path, ft_strlen(path));
		write(STDERR_FILENO, ": No such file or directory\n", 28);
		return (1);
	}
	return (0);
}
