#include "../inc/minishell.h"

//Cette commmand a pour but d'executer une non builtin cmd
//creation d'un child process pour execution de execve 
void	execve_non_builtin(t_token *lst_token, t_shell *shell)
{
	char	*cmd;
	char	**cmd_args;

	cmd = find_cmd_path(lst_token->value, shell->var_env);
	if (!cmd)
	{
		printf("couldnt foudnt the executable path\n");
		exit(EXIT_FAILURE);
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

//Cette fonction permet de trouver le path d'un executable (non builtin cmd)
// dans notre copie de l'environnement
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

//Cette fonction a pour but de join les differents dir d'une path
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

//je parse les tokens pour prendre les arguments des commandes
//par exemple ls -la
char	**find_cmd_args(t_token *lst_token)
{
	char	**cmd_args;
	t_token	*temp;
	int		n;
	int		i;

	temp = lst_token;
	n = 0;
	while (temp && (temp->type == WORD
			|| temp->type == SQUOTE || temp->type == DQUOTE))
	{
		n++;
		temp = temp->next;
	}
	cmd_args = (char **)malloc(sizeof(char *) * (n + 1));
	if (!cmd_args)
		return (NULL);
	i = 0;
	temp = lst_token;
	while (i < n)
	{
		cmd_args[i] = ft_strdup(temp->value);
		i++;
		temp = temp->next;
	}
	cmd_args[n] = '\0';
	return (cmd_args);
}
