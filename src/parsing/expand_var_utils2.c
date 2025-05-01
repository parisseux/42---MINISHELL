#include "../inc/minishell.h"

void	handle_valid_token(t_token *lst_token, t_shell *shell)
{
	t_token	*next;
	int		type;
	int		space;

	next = lst_token->next;
	type = lst_token->type;
	space = lst_token->space;
	which(&lst_token->value, shell);
	lst_token->next = next;
	lst_token->type = type;
	lst_token->space = space;
}

int	spe_case(char *value, int type, int space)
{
	if (!ft_strncmp(value, "$", 2) && (type == SQUOTE
			|| type == DQUOTE) && space == 0)
		return (1);
	return (0);
}
