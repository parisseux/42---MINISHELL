#include "../inc/minishell.h"

int	skip_space(char **input)
{
	int	i;

	i = 0;
	while (**input == ' ' || **input == '\t' || **input == '\v'
		|| **input == '\r' || **input == '\n' || **input == '\f')
	{
		(*input)++;
		i++;
	}
	return (i);
}

int	spaces(char input)
{
	if (input == ' ' || input == '\t' || input == '\v'
		|| input == '\r' || input == '\n' || input == '\f')
		return (1);
	return (0);
}

void	print_token_list(t_token *lst_token)
{
	t_token	*current;

	current = lst_token;
	while (current)
	{
		if (current->value != NULL)
		{
			printf("Token: [%s], Type: %d, Space: %d\n", current->value, current->type, current->space);
		}
		else
		{
			printf("Token: [NULL] ou Type: NULL \n");
		}
		current = current->next;
	}
}

t_token *create_mini_list_token(t_token *lst_token)
{
	t_token *mini_lst;
	t_token *temp;
	t_token *new_token;

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
