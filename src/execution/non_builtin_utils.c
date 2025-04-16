#include "../inc/minishell.h"

char	*look_for_cmd(t_token *temp, t_shell *shell)
{
	char	*cmd;

	cmd = NULL;
	while (temp->type != PIPE && temp->type != END)
	{
		if (temp->type == REDIR_IN || temp->type == REDIR_OUT
			|| temp->type == HEREDOC || temp->type == APPEND)
			temp = temp->next->next;
		else
		{
			cmd = find_cmd_path(temp->value, shell->var_env);
			break ;
		}		
	}
	return (cmd);
}

char	*ft_strjoin_paths(char *dir, char *cmd)
{
	char	*final_path;
	char	*temp;

	final_path = ft_strjoin(dir, "/");
	if (!final_path)
		return (NULL);
	else
		temp = final_path;
	final_path = ft_strjoin(final_path, cmd);
	free(temp);
	return (final_path);
}

int	number_arguments(t_token *lst_token)
{
	t_token	*temp;
	int		n;

	n = 0;
	temp = lst_token;
	while (temp->type != END && temp->type != PIPE)
	{
		if (temp->type == REDIR_IN || temp->type == REDIR_OUT
			|| temp->type == APPEND || temp->type == HEREDOC)
			temp = temp->next->next;
		else
		{
			n++;
			temp = temp->next;
		}
	}
	return (n);
}

char	**find_cmd_args(t_token *lst_token)
{
	char	**cmd_args;
	t_token	*temp;
	int		n;
	int		i;

	n = number_arguments(lst_token);
	cmd_args = (char **)malloc(sizeof(char *) * (n + 1));
	if (!cmd_args)
		return (NULL);
	i = 0;
	temp = lst_token;
	while (i < n)
	{
		if (temp->type == REDIR_IN || temp->type == REDIR_OUT
			|| temp->type == APPEND || temp->type == HEREDOC)
			temp = temp->next->next;
		else
		{
			cmd_args[i] = ft_strdup(temp->value);
			i++;
			temp = temp->next;
		}
	}
	cmd_args[n] = '\0';
	return (cmd_args);
}

char	*find_cmd_path(char *cmd, char **env)
{
	char	*path;
	char	**paths;
	int		i;
	char	*final_path;

	path = get_env_value(env, "PATH");
	if (!path)
		return (NULL);
	paths = ft_split(path, ':');
	i = 0;
	while (paths[i])
	{
		final_path = ft_strjoin_paths(paths[i], cmd);
		if (access(final_path, X_OK) == 0)
		{
			ft_free_char_tab(paths);
			return (final_path);
		}
		free(final_path);
		i++;
	}
	ft_free_char_tab(paths);
	return (NULL);
}
