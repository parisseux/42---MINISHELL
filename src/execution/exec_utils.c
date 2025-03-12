#include "../inc/minishell.h"

//Cette fonction permet d'aller chercher dans
//la copie de notre environnement (char **)
//le contenue d'une variable 
//exemple si key = PATH alors la fonction retourne /usr/bin....
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

//cherche la presence de pipe dans lst de token
int	is_pipe(t_token *lst_token)
{
	t_token	*temp;

	temp = lst_token;
	while (temp->type != END)
	{
		if (temp->type == PIPE)
			return (1);
		temp = temp->next;
	}
	return (0);
}

//cherche la presence de builtin dans la lst de token
int	is_builtin(t_token *lst_token)
{
	t_token	*temp;

	temp = lst_token;
	while (temp->type != END)
	{
		if (temp->type == WORD)
		{
			if (!ft_strncmp(temp->value, "echo", 5))
				return (1);
			else if (!ft_strncmp(temp->value, "cd", 3))
				return (1);
			else if (!ft_strncmp(temp->value, "pwd", 4))
				return (1);
			else if (!ft_strncmp(temp->value, "export", 7))
				return (1);
			else if (!ft_strncmp(temp->value, "unset", 5))
				return (1);
			else if (!ft_strncmp(temp->value, "env", 4))
				return (1);
			else if (!ft_strncmp(temp->value, "exit", 6))
				return (1);
		}
		temp = temp->next;
	}
	return (0);
}

//cherche la presence de redirection dans la lst de token
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
