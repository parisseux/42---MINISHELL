#include "../inc/minishell.h"

int		space(t_token *lst_token)
{
	int	type;

	type = lst_token->next->type;
	if (type == END || type == PIPE || type == APPEND || type == REDIR_OUT || type == HEREDOC || type == BIN || type == REDIR_IN)
		return (1);
	if (lst_token->space == 1)
		return (0);

	return (0);
}

char	*add_home(char *home, char *str)
{
	char	*new;
	int 	size;
	int		j;
	int		i;

	i = 0;
	size = ft_strlen(home) + ft_strlen(str);
	new = malloc(sizeof(char) * size);
	if (!new)
		return (NULL);
	while (str[i] != '~')
		i++;
	ft_strlcpy(new, str, i + 1);
	ft_strlcat(new, home, size);
	j = i + ft_strlen(home);
	i++;
	while (str[i] != '\0')
	{
		new[j] = str[i];
		i++;
		j++;
	}
	new[j] = '\0';
	free(str);
	return (new);
}

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

void	expand_home(t_shell *shell, t_token *lst_token)
{
	int		i;
	char	*home;
	char	*tmp;

	i = 0;
	while (lst_token->type != END)
	{
		if (lst_token->next->type == WORD && before(lst_token) && space(lst_token->next))
		{
			tmp = ft_strdup(lst_token->next->value);
			i = 0;
			while (lst_token->next->value[i] != '\0')
			{
				if (lst_token->next->value[i] == '~' && ishome(lst_token->next->value, i))
				{
					home = get_env_value(shell->var_env, "HOME");
					if (!home)
					{
						write(STDOUT_FILENO, "cd: HOME not set\n", 17);
						shell->exit = 1;
						return ;
					}
					free(lst_token->next->value);
					lst_token->next->value = add_home(home, tmp);
					tmp = ft_strdup(lst_token->next->value);
					i = 0;
				}
				else
					i++;
			}
			free(tmp);
		}
		lst_token = lst_token->next;
	}
}
