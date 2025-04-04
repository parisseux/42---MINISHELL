#include "../inc/minishell.h"

int	is_bin_path(t_token *lst_token)
{
	t_token	*tmp;

	tmp = lst_token;
	while (tmp->type != END)
	{
		if (tmp->type == BIN)
			return (1);
		tmp = tmp->next;
	}
	return (0);
}
// n'existe pas ?

void	cmd_not_found(t_token *lst_token)
{
	write(STDERR_FILENO, "minishell: ", 11);
	write(STDERR_FILENO, lst_token->value, ft_strlen(lst_token->value));
	write(STDERR_FILENO, " command not found\n", 19);
	exit(127);
}

void	execve_bin_token(t_token *lst_token, t_shell *shell)
{
	char	*cmd;
	char	**cmd_args;

	cmd = lst_token->value;
	if (!cmd)
		cmd_not_found(lst_token);
	cmd_args = find_cmd_args(lst_token);
	if (!cmd_args)
		exit(EXIT_FAILURE);
	if (execve(cmd, cmd_args, shell->var_env) == -1)
	{
		perror("execve");
		exit(EXIT_FAILURE);
	}
}

t_token	*bin_path(char **input)
{
	t_token	*new_token;
	char	*start;
	char	*value;
	int		len;

	start = *input;
	while (!spaces(**input) && !ft_strchr("|<> \'\"", **input) && **input)
		(*input)++;
	len = *input - start;
	value = (char *)malloc(sizeof(char) * (len + 1));
	if (!value)
		return (NULL);
	ft_strlcpy(value, start, len + 1);
	new_token = create_token(value, BIN);
	free(value);
	return (new_token);
}
