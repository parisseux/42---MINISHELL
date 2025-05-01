/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchatagn <pchatagn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 16:24:01 by pchatagn          #+#    #+#             */
/*   Updated: 2025/05/01 16:24:03 by pchatagn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	count_argument_cd(t_token *lst_token)
{
	int		n;
	t_token	*temp;

	n = 0;
	temp = lst_token;
	while (temp->type != END && temp->type != PIPE)
	{
		if (temp->type == REDIR_IN || temp->type == REDIR_OUT
			|| temp->type == APPEND || temp->type == HEREDOC)
			temp = temp->next->next;
		else if (temp->type == WORD || temp->type == SQUOTE
			|| temp->type == DQUOTE || temp->type == BIN)
		{
			n++;
			temp = temp->next;
		}
		else
			temp = temp->next;
	}
	return (n);
}

int	move_to_path(char *path, t_shell *shell)
{
	char	*home;

	home = NULL;
	if (!path)
	{
		home = env_value(shell, shell->var_env, "HOME");
		if (!home)
		{
			write(STDERR_FILENO, "cd: HOME not set\n", 17);
			return (1);
		}
		path = home;
	}
	if (chdir(path) == -1)
	{
		write(STDERR_FILENO, "cd: ", 4);
		write(STDERR_FILENO, path, ft_strlen(path));
		write(STDERR_FILENO, ": No such file or directory\n", 28);
		return (1);
	}
	return (0);
}

int	cd_command(t_token *lst, t_shell *shell)
{
	char	*path;

	path = NULL;
	if (count_argument_cd(lst) > 1)
	{
		write(STDERR_FILENO, "cd: too many arguments\n", 23);
		return (1);
	}
	while (lst->type != PIPE && lst->type != END)
	{
		if (lst->type == REDIR_IN || lst->type == REDIR_OUT
			|| lst->type == HEREDOC || lst->type == APPEND)
		{
			lst = lst->next->next;
			continue ;
		}
		if ((lst->type == WORD || lst->type == SQUOTE
				|| lst->type == DQUOTE || lst->type == BIN))
		{
			path = lst->value;
			break ;
		}
	}
	move_to_path(path, shell);
	return (0);
}
