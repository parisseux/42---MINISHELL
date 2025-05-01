/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_shell_var.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchatagn <pchatagn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 16:26:22 by pchatagn          #+#    #+#             */
/*   Updated: 2025/05/01 16:26:23 by pchatagn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	redirtype(int type)
{
	if (type == APPEND || type == REDIR_IN
		|| type == REDIR_IN || type == HEREDOC)
		return (1);
	return (0);
}

int	in_shell_env(t_token *tmp)
{
	if (is_pipe(tmp))
		return (0);
	while (tmp->type != END)
	{
		if (not_cmd(tmp) || !ft_strncmp(tmp->value, "export", 7))
			return (0);
		if (redirtype(tmp->type) == 1)
			if (tmp->next->type != END)
				tmp = tmp->next->next;
		if (tmp->type != END)
			tmp = tmp->next;
	}
	return (1);
}
