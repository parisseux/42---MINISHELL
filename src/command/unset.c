#include "../inc/minishell.h"

int	invalid_option(char *line, t_shell *shell)
{
	if (!ft_strncmp(line, "-", 1))
	{
		write(STDERR_FILENO, "minishell: unset: -", 19);
		write(STDERR_FILENO, &line[1], 1);
		write(STDERR_FILENO, ": invalid option\n", 17);
		write(STDERR_FILENO, "unset: usage: unset", 19);
		write(STDERR_FILENO, " [-f] [-v] [-n] [name ...]\n", 27);
		shell->exit = 2;
		return (1);
	}
	return (0);
}

int	remove_var(char **env, char *line)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (!ft_varcmp(env[i], line, ft_strlen(line)))
		{
			free(env[i]);
			while (env[i])
			{
				env[i] = env[i + 1];
				i++;
			}
			return (1);
		}
		i++;
	}
	return (0);
}

int	unset_command(t_token *lst, t_shell *shell)
{
	while (lst->type != END && lst->type != PIPE)
	{
		if (lst->type == REDIR_IN || lst->type == REDIR_OUT
			|| lst->type == APPEND || lst->type == HEREDOC)
		{
			lst = lst->next->next;
			continue ;
		}
		if (lst->type == WORD || lst->type == SQUOTE
			|| lst->type == DQUOTE || lst->type == BIN || lst->type == DEF)
		{
			if (invalid_option(lst->value, shell))
				return (1);
			remove_var(shell->var_env, lst->value);
			if (shell->shell_env)
				remove_var(shell->shell_env, lst->value);
		}
		lst = lst->next;
	}
	return (0);
}
