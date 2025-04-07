#include "../inc/minishell.h"

t_token	*create_mini_list(t_token **lst_token)
{
	t_token	*mini_lst;

	mini_lst = create_mini_list_token(*lst_token);
	go_to_next_pipe(lst_token);
	return (mini_lst);
}

void	handle_first_cmd(t_token *lst, t_shell *shell,
	int pipefd[][2], int n_pipes)
{
	dup2(pipefd[0][1], STDOUT_FILENO);
	close(pipefd[0][1]);
	close(pipefd[0][0]);
	close_all_pipes_except(pipefd, 0, n_pipes);
	exec_one_cmd(lst, shell);
	exit(1);
}

void	handle_last_cmd(t_token *lst, t_shell *shell,
	int pipefd[][2], int n_pipes)
{
	dup2(pipefd[n_pipes - 1][0], STDIN_FILENO);
	close(pipefd[n_pipes - 1][0]);
	close(pipefd[n_pipes - 1][1]);
	close_all_pipes_except(pipefd, n_pipes, n_pipes);
	exec_one_cmd(lst, shell);
	exit(1);
}

void	handle_middle_cmd(t_token *lst, t_shell *shell,
	int pipefd[][2], int i, int n_pipes)
{
	dup2(pipefd[i - 1][0], STDIN_FILENO);
	close(pipefd[i - 1][0]);
	dup2(pipefd[i][1], STDOUT_FILENO);
	close(pipefd[i][1]);
	close(pipefd[i][0]);
	close(pipefd[i - 1][1]);
	close_all_pipes_except(pipefd, i, n_pipes);
	exec_one_cmd(lst, shell);
	exit(1);
}
