#include "../inc/minishell.h"

int	is_bin_path(t_token *lst_token)
{
	t_token	*tmp;

	tmp = lst_token;
	while (tmp->type != END && tmp->type != PIPE)
	{
		if (tmp->type == REDIR_IN || tmp->type == REDIR_OUT
			|| tmp->type == APPEND || tmp->type == HEREDOC)
			tmp = tmp->next ;
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

	while (lst_token->type != PIPE && lst_token->type != END)
	{
		if (lst_token->type == REDIR_IN || lst_token->type == REDIR_OUT
			|| lst_token->type == HEREDOC || lst_token->type == APPEND)
			lst_token = lst_token->next->next;
		if (lst_token->next->space == 1 || lst_token->next->type == PIPE
			|| lst_token->next->type == END)
		{
			cmd = lst_token->value;
			if (!cmd)
				cmd_not_found(lst_token);
			break ;
		}
	}
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
