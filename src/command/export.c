/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avarrett <avarrett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 16:24:24 by pchatagn          #+#    #+#             */
/*   Updated: 2025/05/01 17:27:13 by avarrett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	print_export(t_shell *shell)
{
	int	i;

	i = 0;
	while (shell->venv[i])
	{
		write(STDERR_FILENO, "declare -x ", 11);
		write(STDERR_FILENO, shell->venv[i], ft_strlen(shell->venv[i]));
		write(STDERR_FILENO, "\n", 1);
		i++;
	}
}

void	new_tab(char **venv, char *value, char **new_env)
{
	int	j;

	j = 0;
	if (tab_len(venv) == 1 && ft_strlen(venv[j]) == 0)
		new_env[j] = ft_strdup(value);
	else
	{
		while (venv[j] != NULL)
		{
			new_env[j] = ft_strdup(venv[j]);
			j++;
		}
		new_env[j] = ft_strdup(value);
	}
	new_env[j + 1] = NULL;
}

char	**add_var_to_env(char **venv, char *value)
{
	int		i;
	int		j;
	char	**tmp;

	j = 0;
	i = 0;
	while (value[j] != '=')
		j++;
	tmp = venv;
	i = found_in_tab(tmp, value, j);
	if (i >= 0)
	{
		free(venv[i]);
		venv[i] = ft_strdup(value);
		return (venv);
	}
	else
	{
		tmp = ft_calloc(sizeof(char **), tab_len(tmp) + 2);
		new_tab(venv, value, tmp);
		ft_free_char_tab(venv);
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

	tmp = lst_token->next;
	if (tmp->type == END)
	{
		print_export(shell);
		return (0);
	}
	while (tmp->type != END)
	{
		if (invalid_export_type(tmp->type))
			tmp = tmp->next;
		if (tmp->type == DEF || (ft_strchr(tmp->value, '=')
				&& !good_varname(tmp->value, '=')))
			shell->venv = add_var_to_env(shell->venv, tmp->value);
		else if (bad_export(tmp->value))
			export_message_error(tmp->value, shell);
		tmp = tmp->next;
	}
	return (shell->exit);
}
