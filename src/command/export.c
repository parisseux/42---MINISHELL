#include "../inc/minishell.h"

// a revoir
//meme chose il faut introduire fd_out et corriger les prints pour des write
// ATTETION SI SHELL VIDE
void	print_export(t_shell *shell, int fd_out)
void	print_export(t_shell *shell)
{
	int	i;
	// int	saved_stdout;

	i = 0;
	// saved_stdout = dup(STDOUT_FILENO);
	// if (fd_out != -1)
	// {
	// 	dup2(fd_out, STDOUT_FILENO);
	// 	close(fd_out);
	// }
	while (shell->var_env[i])
	{
		write(STDOUT_FILENO, "declare -x ", 11);
		write(STDOUT_FILENO, shell->var_env[i], ft_strlen(shell->var_env[i]));
		write(STDOUT_FILENO, "\n", 1);
		i++;
	}
	// dup2(saved_stdout, STDOUT_FILENO);
	// close(saved_stdout);
}

char **new_tab(char **var_env, char *value, char **new_env, int add)
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
	int	i;
	int	j;
	int check;
	char	**tmp;

	i = 0;
	j = 0;
	check = 0;
	while (value[j] != '=')
		j++;
	while (var_env && var_env[i] != NULL)
	{
		if (!ft_varcmp(var_env[i], value, j))
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
	return (0);
}

void	export_message_error(char *value, t_shell *shell)
{
	if (!ft_strncmp(value, "-", 1))
	{
		write(STDOUT_FILENO, "minishell: export: -", 20);
		write(STDOUT_FILENO, &value[1], 1);
		write(STDOUT_FILENO, ": invalid option\n", 17);
		write(STDOUT_FILENO, "export: usage: export [-fn] [name[=value] ...] or export -p\n", 60);
		shell->exit = 2;	
	}
	else
	{
		write(STDERR_FILENO, "minishell: export: `", 20);
		write(STDERR_FILENO, value, ft_strlen(value));
		write(STDERR_FILENO, "': not a valid identifier\n", 26);
		shell->exit = 1;		
	}
	
}

void	export_command(t_token *lst_token, t_shell *shell, int fd_out)
{
	t_token	*tmp;
	char	**tab;

	tmp = lst_token->next;
	if (tmp->type == END)
	{
		print_export(shell);
		return ;
	}
	while (tmp->type != END)
	{
		if (tmp->type == DEF || (ft_strchr(tmp->value, '=') && !good_varname(tmp->value, '=')))
		{
			tab = add_var_to_env(shell->var_env, tmp->value, 0);
			ft_free_char_tab(shell->var_env);
			shell->var_env = tab;
		}
		else if ((ft_strchr(tmp->value, '=') && good_varname(tmp->value, '=')) || good_varname(tmp->value, '\0'))
			return (export_message_error(tmp->value, shell));
		else
			return ;
		tmp = tmp->next;
	}
}

