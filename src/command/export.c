#include "../inc/minishell.h"

// a revoir
//meme chose il faut introduire fd_out et corriger les prints pour des write
void	print_export(t_shell *shell, int fd_out)
{
	int	i;
	int	saved_stdout;

	i = 0;
	saved_stdout = dup(STDOUT_FILENO);
	if (fd_out != -1)
	{
		dup2(fd_out, STDOUT_FILENO);
		close(fd_out);
	}
	while (shell->var_env[i])
	{
		write(STDOUT_FILENO, "declare -x ", 11);
		write(STDOUT_FILENO, shell->var_env[i], ft_strlen(shell->var_env[i]));
		write(STDOUT_FILENO, "\n", 1);
		i++;
	}
	dup2(saved_stdout, STDOUT_FILENO);
	close(saved_stdout);
}

// add a la fin pas exactement pareil mais bon ...
int	add_var_to_env(char **var_env, char *value, int shell)
{
	int	i;
	int	j;
	int	check;

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
			return (1);
		}
		i++;
	}
	if (!check && shell == 0)
	{
		var_env[i] = ft_strdup(value);
		var_env[i + 1] = NULL;			
	}
	return (0);
}

int	good_varname(char *name)
{
	int	i;

	i = 0;
	while (name[i] != '=')
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
	printf("minishell: export: `%s': not a valid identifier\n", value);
	shell->exit = 1;
}

void	export_command(t_token *lst_token, t_shell *shell, int fd_out)
{
	t_token	*tmp;

	tmp = lst_token->next;
	if (tmp->type == END)
	{
		print_export(shell, fd_out);
		return ;
	}
	while (tmp->type != END)
	{
		if (ft_strchr(tmp->value, '='))
		{
			if (good_varname(tmp->value))
			{
				export_message_error(tmp->value, shell);
				return ;
			}
			else
				add_var_to_env(shell->var_env, tmp->value, 0);
		}
		tmp = tmp->next;
	}
}
