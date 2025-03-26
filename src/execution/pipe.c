#include "../inc/minishell.h"


t_token *create_mini_list(t_token **lst_token)
{
	t_token *mini_lst;

	mini_lst = create_mini_list_token(*lst_token);
	go_to_next_pipe(lst_token);
	return (mini_lst);
}
//dup2(old_fd, new_fd);

void handle_first_cmd(t_token *lst, t_shell *shell, int pipefd[][2])
{
	close(pipefd[0][0]);
	dup2(pipefd[0][1], STDOUT_FILENO);
	exec_one_cmd(lst, shell);
	exit(0);
}


void handle_last_cmd(t_token *lst, t_shell *shell, int pipefd[][2], int n_pipes)
{
	close(pipefd[n_pipes][1]);
	dup2(pipefd[n_pipes - 1][0], STDIN_FILENO);
	exec_one_cmd(lst, shell);
	exit(0);
}

void handle_middle_cmd(t_token *lst, t_shell *shell, int pipefd[][2], int i)
{
	dup2(pipefd[i - 1][0], STDIN_FILENO);
	dup2(pipefd[i][1], STDOUT_FILENO);
	exec_one_cmd(lst, shell);
	exit(0);
}