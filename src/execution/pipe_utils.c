#include "../inc/minishell.h"

void	wait_all_pids(int *pids, int *status, int n_cmd)
{
	int	i;

	i = 0;
	while (i < n_cmd)
	{
		waitpid(pids[i], status, 0);
		i++;
	}
}

void	create_all_pipes(int pipefd[][2], int n_pipes)
{
	int	i;

	i = 0;
	while (i < n_pipes)
	{
		if (pipe(pipefd[i]) == -1)
			return (perror("pipe"));
		i++;
	}
}

void	go_to_next_pipe(t_token **lst_token)
{
	if (!lst_token || !*lst_token)
		return ;
	while (*lst_token && (*lst_token)->type != PIPE
		&& (*lst_token)->type != END)
		*lst_token = (*lst_token)->next;
	if (*lst_token && (*lst_token)->type == PIPE)
		*lst_token = (*lst_token)->next;
}

t_token	*create_mini_list_token(t_token *lst_token)
{
	t_token	*mini_lst;
	t_token	*temp;
	t_token	*new_token;

	mini_lst = NULL;
	temp = lst_token;
	while (temp != NULL && temp->type != PIPE && temp->type != END)
	{
		new_token = create_token(temp->value, temp->type);
		add_token_to_lst(&mini_lst, new_token, temp->space);
		temp = temp->next;
	}
	new_token = create_token("", END);
	add_token_to_lst(&mini_lst, new_token, 0);
	return (mini_lst);
}
