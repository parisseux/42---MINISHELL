#include "../inc/minishell.h"

char	*get_env_value(char **env, char *key)
{
	int	i;
	int	len;

	len = ft_strlen(key);
	i = 0;
	while (env[i])
	{
		if ((ft_strncmp(env[i], key, len) == 0 && env[i][len] == '='))
		{
			return (env[i] + len + 1);
		}
		i++;
	}
	return (NULL);
}

int	is_pipe(t_token *lst_token)
{
	t_token	*temp;
	int		pipe;

	pipe = 0;
	temp = lst_token;
	while (temp->type != END)
	{
		if (temp->type == PIPE)
			pipe++;
		temp = temp->next;
	}
	return (pipe);
}

int	is_def(t_token *lst_token)
{
	t_token	*temp;

	temp = lst_token;
	while (temp->type != END)
	{
		if (temp->type == DEF)
			return (1);
		temp = temp->next;
	}
	return (0);
}

int is_cmd_before_builtin(t_token *builtin, t_token *lst_token)
{
	t_token *temp;

	temp = lst_token;
	while (temp != builtin && temp->type != END && temp->type != PIPE)
	{
		if (temp->type == REDIR_IN || temp->type == REDIR_OUT
			|| temp->type == APPEND || temp->type == HEREDOC)
		{
			temp = temp->next;
			if (temp)
				temp = temp->next;
		}
		else if (temp->type == WORD || temp->type == SQUOTE || temp->type == DQUOTE
			|| temp->type == DEF || temp->type == BIN)
			return (1);
		else 
			temp = temp->next;
	}
			
	return (0);
}

int	is_builtin(t_token *lst_token)
{
	t_token	*temp;

	temp = lst_token;
	while (temp->type != END && temp->type != PIPE)
	{
		if (temp->type == WORD && (temp->next->space == 1 || temp->next->type == END
			|| temp->next->type == PIPE))
		{
			if (!ft_strncmp(temp->value, "echo", 5) || !ft_strncmp(temp->value, "cd", 3)
				|| !ft_strncmp(temp->value, "pwd", 4) || !ft_strncmp(temp->value, "export", 7)
				|| !ft_strncmp(temp->value, "unset", 5) || !ft_strncmp(temp->value, "env", 4)
				|| !ft_strncmp(temp->value, "exit", 6))
				{
					if (is_cmd_before_builtin(temp, lst_token) == 0)
						return (1);
				}
		}
		temp = temp->next;
	}
	return (0);
}

int	is_redir(t_token *lst_token)
{
	t_token	*temp;

	temp = lst_token;
	while (temp->type != END)
	{
		if (temp->type == HEREDOC)
			return (1);
		else if (temp->type == APPEND)
			return (2);
		else if (temp->type == REDIR_IN)
			return (3);
		else if (temp->type == REDIR_OUT)
			return (4);
		temp = temp->next;
	}
	return (0);
}
