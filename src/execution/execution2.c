/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avarrett <avarrett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 16:24:41 by pchatagn          #+#    #+#             */
/*   Updated: 2025/05/01 17:27:13 by avarrett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	execve_non_builtin(t_token *lst_token,
	t_shell *shell)
{
	char	*cmd;
	char	**cmd_args;
	t_token	*temp;

	cmd = NULL;
	temp = lst_token;
	cmd = look_for_cmd(&temp, shell);
	if (!cmd)
		cmd_not_found(temp);
	cmd_args = find_cmd_args(temp);
	if (!cmd_args)
		exit(EXIT_FAILURE);
	if (execve(cmd, cmd_args, shell->venv) == -1)
	{
		perror("execve");
		exit(EXIT_FAILURE);
	}
}

int	non_builtin_child(t_token *lst_token, t_shell *shell)
{
	if (handle_redir(lst_token, shell))
		return (1);
	init_exec_child_signals();
	if (is_bin_path(lst_token))
		execve_bin_token(lst_token, shell);
	else
		execve_non_builtin(lst_token, shell);
	return (0);
}

void	fork_and_exec_pipe(t_pipe *p, t_shell *shell)
{
	int	i;

	i = 0;
	while (i < p->n_pipes + 1)
	{
		p->pids[i] = fork();
		if (p->pids[i] == 0)
		{
			if (i == 0)
				handle_first_cmd(p, shell);
			else if (i == p->n_pipes)
				handle_last_cmd(p, shell);
			else
				handle_middle_cmd(p, shell, i);
		}
		i++;
	}
}
