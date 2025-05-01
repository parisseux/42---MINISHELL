/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchatagn <pchatagn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 16:24:53 by pchatagn          #+#    #+#             */
/*   Updated: 2025/05/01 16:24:54 by pchatagn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	handle_first_cmd(t_pipe *p, t_shell *shell)
{
	dup2(p->pipefd[0][1], STDOUT_FILENO);
	close(p->pipefd[0][1]);
	close(p->pipefd[0][0]);
	close_all_pipes_except(p->pipefd, 0, p->n_pipes);
	exec_one_cmd(p->cmds[0], shell);
	exit(1);
}

void	handle_last_cmd(t_pipe *p, t_shell *shell)
{
	int	last;

	last = p->n_pipes -1;
	dup2(p->pipefd[last][0], STDIN_FILENO);
	close(p->pipefd[last][0]);
	close(p->pipefd[last][1]);
	close_all_pipes_except(p->pipefd, p->n_pipes, p->n_pipes);
	exec_one_cmd(p->cmds[p->n_pipes], shell);
	exit(1);
}

void	handle_middle_cmd(t_pipe *p, t_shell *shell, int i)
{
	dup2(p->pipefd[i - 1][0], STDIN_FILENO);
	close(p->pipefd[i - 1][0]);
	dup2(p->pipefd[i][1], STDOUT_FILENO);
	close(p->pipefd[i][1]);
	close(p->pipefd[i][0]);
	close(p->pipefd[i - 1][1]);
	close_all_pipes_except(p->pipefd, i, p->n_pipes);
	exec_one_cmd(p->cmds[i], shell);
	exit(1);
}
