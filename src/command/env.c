/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avarrett <avarrett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 16:24:12 by pchatagn          #+#    #+#             */
/*   Updated: 2025/05/01 17:27:13 by avarrett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	print_env(t_shell *shell)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	while (shell->venv[i])
	{
		len = ft_strlen(shell->venv[i]);
		if (len == 0)
			return (0);
		write(STDOUT_FILENO, shell->venv[i], len);
		write(STDOUT_FILENO, "\n", 1);
		i++;
	}
	return (0);
}

int	env_command(t_shell *shell, t_token *lst)
{
	while (lst->type != PIPE && lst->type != END)
	{
		if (lst->next->type == END || lst->next->type == PIPE)
			return (print_env(shell));
		else if (lst->type == APPEND || lst->type == REDIR_IN
			|| lst->type == REDIR_OUT || lst->type == HEREDOC)
			lst = lst->next->next;
		else
		{
			ft_putstr_fd("env ", 2);
			ft_putstr_fd(lst->next->value, 2);
			ft_putstr_fd(": No such file or directory\n", 2);
			return (127);
		}
	}
	return (1);
}
