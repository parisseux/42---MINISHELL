/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_u.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avarrett <avarrett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 16:24:21 by pchatagn          #+#    #+#             */
/*   Updated: 2025/05/01 17:20:08 by avarrett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	export_message_error(char *value, t_shell *shell)
{
	if (!ft_strncmp(value, "-", 1))
	{
		write(STDERR_FILENO, "minishell: export: -", 20);
		write(STDERR_FILENO, &value[1], 1);
		write(STDERR_FILENO, ": invalid option\n", 17);
		write(STDERR_FILENO, "export: usage: export [-fn]", 17);
		write(STDERR_FILENO, " [name[=value] ...] or export -p\n", 33);
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

int	found_in_tab(char **venv, char *value, int len)
{
	int	i;

	i = 0;
	while (venv && venv[i] != NULL)
	{
		if (!ft_varcmp(venv[i], value, len))
			return (i);
		i++;
	}
	return (-1);
}

int	tab_len(char **tab)
{
	int	i;

	i = 0;
	while (tab[i] != NULL)
		i++;
	return (i);
}

int	invalid_export_type(int type)
{
	if (type == REDIR_IN || type == REDIR_OUT
		|| type == HEREDOC || type == APPEND)
		return (1);
	return (0);
}

int	bad_export(char	*value)
{
	if ((ft_strchr(value, '=') && good_varname(value, '='))
		|| good_varname(value, '\0'))
		return (1);
	return (0);
}
