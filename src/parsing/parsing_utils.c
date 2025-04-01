#include "../inc/minishell.h"

int	skip_space(char **input)
{
	int i;

	i = 0;
	while (**input == ' ' || **input == '\t' || **input == '\v'
		|| **input == '\r' ||**input == '\n' || **input == '\f')
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
