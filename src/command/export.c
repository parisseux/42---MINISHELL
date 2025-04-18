#include "../inc/minishell.h"

void	print_export(t_shell *shell)
{
	int	i;

	i = 0;
	while (shell->var_env[i])
	{
		write(STDERR_FILENO, "declare -x ", 11);
		write(STDERR_FILENO, shell->var_env[i], ft_strlen(shell->var_env[i]));
		write(STDERR_FILENO, "\n", 1);
		i++;
	}
}

char	**new_tab(char **var_env, char *value, char **new_env, int add)
{
	int		j;

	j = 0;
	if (add == 1)
	{
		while (var_env[j] != NULL)
		{
			if (var_env[j + 1] == NULL)
			{
				new_env[j] = ft_strdup(var_env[j]);
				new_env[j + 1] = ft_strdup(value);
			}
			else
				new_env[j] = ft_strdup(var_env[j]);
			j++;
		}		
	}
	else
	{
		while (var_env[j] != NULL)
		{
			new_env[j] = ft_strdup(var_env[j]);
			j++;
		}
	}
	return (new_env);
}

char	**add_var_to_env(char **var_env, char *value, int shell)
{
	int		i;
	int		j;
	int		check;
	char	**tmp;

	i = 0;
	j = 0;
	check = 0;
	while (value[j] != '=')
		j++;
	while (var_env && var_env[i] != NULL)
	{
		if (!ft_varcmp(var_env[i], value, j) || ft_strlen(var_env[i]) == 0)
		{
			free(var_env[i]);
			var_env[i] = ft_strdup(value);
			check = 1;
		}
		i++;
	}
	if (check == 1)
	{
		tmp = ft_calloc(sizeof(char *), i + 1);
		new_tab(var_env, value, tmp, 0);
		return (tmp);
	}
	if (shell == 0)
	{
		tmp = ft_calloc(sizeof(char *), i + 2);
		new_tab(var_env, value, tmp, 1);
		return (tmp);
	}		
	return (NULL);
}

int	good_varname(char *name, char until)
{
	int	i;

	i = 0;
	if (ft_isdigit(name[0]))
		return (1);
	while (name[i] != until)
	{
		if (!ft_isalnum(name[i]) && name[i] != '_')
			return (1);
		i++;
	}
	if (i == 0)
		return (1);
	else if (i == 1 && name[0] == '_')
		return (1);
	return (0);
}

int	export_command(t_token *lst_token, t_shell *shell)
{
	t_token	*tmp;
	char	**tab;

	tmp = lst_token->next;
	if (tmp->type == END)
	{
		print_export(shell);
		return (0);
	}
	while (tmp->type != END)
	{
		if (tmp->type == REDIR_IN || tmp->type == REDIR_OUT
			|| tmp->type == HEREDOC || tmp->type == APPEND)
			tmp = tmp->next;
		if (tmp->type == DEF || (ft_strchr(tmp->value, '=')
				&& !good_varname(tmp->value, '=')))
		{
			tab = add_var_to_env(shell->var_env, tmp->value, 0);
			ft_free_char_tab(shell->var_env);
			shell->var_env = tab;
		}
		else if ((ft_strchr(tmp->value, '=') && good_varname(tmp->value, '='))
			|| good_varname(tmp->value, '\0'))
			export_message_error(tmp->value, shell);
		tmp = tmp->next;
	}
	return (0);
}
