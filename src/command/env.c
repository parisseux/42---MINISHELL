/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchatagn <pchatagn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 16:24:12 by pchatagn          #+#    #+#             */
/*   Updated: 2025/05/05 15:53:20 by pchatagn         ###   ########.fr       */
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

int	skip_redirs(t_token **tok)
{
	while (*tok && ((*tok)->type == REDIR_OUT || (*tok)->type == APPEND
			|| (*tok)->type == REDIR_IN || (*tok)->type == HEREDOC))
		*tok = (*tok)->next->next;
	return (*tok != NULL);
}

int	env_error(char *arg)
{
	ft_putstr_fd("env: ", 2);
	ft_putstr_fd(arg, 2);
	ft_putstr_fd(": No such file or directory\n", 2);
	return (127);
}

int	env_command(t_shell *shell, t_token *lst)
{
	if (!skip_redirs(&lst) || ft_strncmp(lst->value, "env", 4))
		return (1);
	lst = lst->next;
	if (!lst || lst->type == END || lst->type == PIPE)
		return (print_env(shell));
	if (skip_redirs(&lst) && (lst->type == END || lst->type == PIPE))
		return (print_env(shell));
	return (env_error(lst->value));
}
