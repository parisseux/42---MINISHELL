#include "../inc/minishell.h"

//dup2(old_fd, new_fd);

void handle_first_cmd(t_token **lst_token, t_shell *shell, int pipefd[][2], int n_pipes)
{
	// close(pipefd[0][0]);
	// dup2(pipefd[0][1], STDOUT_FILENO);
	// close(pipefd[0][1]);
	t_token *mini_lst;

	mini_lst = create_mini_list_token(*lst_token);
	if (mini_lst)
		print_token_list(mini_lst);
	// while (lst_token->type != PIPE || lst_token->type != END)
	// {
	// 	if (lst_token->type = DEF)
	// 	{
	// 		go_to_next_pipe(lst_token);
	// 		return ;
	// 	}
		
		   
	// 	lst_token = lst_token->next;
	// }
	(void)shell;
	(void)pipefd;
	(void)n_pipes;
	free_token_list(mini_lst);
	go_to_next_pipe(lst_token);
}


void handle_last_cmd(t_token **lst_token, t_shell *shell, int pipefd[][2], int n_pipes)
{
	// close(pipefd[n_pipes - 1][1]);
	// dup2(pipefd[n_pipes - 1][0], STDIN_FILENO);
	// close(pipefd[n_pipes - 1][0]);
	t_token *mini_lst;
	ft_putchar_fd('a', 1);

	mini_lst = create_mini_list_token(*lst_token);
	if (mini_lst)
		print_token_list(mini_lst);

	// while (lst_token->type != END)
	// {
	// 	if (lst_token->type = DEF)
	// 	{
	// 		go_to_next_pipe(lst_token);
	// 		return ;
	// 	}
		
	// 	lst_token = lst_token->next;
	// }
	(void)shell;
	(void)pipefd;
	(void)n_pipes;
	free_token_list(mini_lst);
	go_to_next_pipe(lst_token);
}

// handle_middle_cmd(lst_token, shell, i, pipefd);