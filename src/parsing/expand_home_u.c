#include "../inc/minishell.h"

int	ishome(char *str, int i)
{
	if (str[i - 1] != ' ' && i - 1 >= 0)
		return (0);
	if (str[i + 1] != ' ' && str[i + 1] != '/' && str[i + 1] != '\0')
		return (0);
	return (1);
}

int	before(t_token *lst_token)
{
	if (lst_token->next->space == 0 && lst_token->type == SQUOTE)
		return (0);
	return (1);
}

int	isvalid(int type, char *str)
{
	char	*after;

	after = NULL;
	if (str == NULL)
		return (0);
	if (type != WORD && type != DQUOTE && type != DEF)
		return (0);
	if (!ft_strchr(str, '$'))
		return (0);
	else
		after = ft_strchr(str, '$');
	if (after[1] == ' ' || after[1] == '\0' || after[1] == '/')
		return (0);
	return (1);
}

void	init(int *i, char **name, char **dup, char *value)
{
	*i = 0;
	*name = NULL;
	*dup = value;
}
