#include "../inc/minishell.h"

int	space(t_token *lst_token)
{
	int	type;

	if (lst_token->type == END)
		return (0);
	type = lst_token->next->type;
	if (type == END || type == PIPE || type == APPEND || type == REDIR_OUT
		|| type == HEREDOC || type == BIN || type == REDIR_IN)
		return (1);
	if (lst_token->space == 1)
		return (0);
	return (0);
}

char	*add_home(char *home, char *str)
{
	char	*new;
	int		size;
	int		j;
	int		i;

	i = 0;
	size = ft_strlen(home) + ft_strlen(str);
	new = malloc(sizeof(char) * size + 1);
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

void	home_not_set(t_shell *shell)
{
	write(STDOUT_FILENO, "cd: HOME not set\n", 17);
	shell->exit = 1;
}

void	replace_home(t_token *lst, char	*home)
{
	char	*tmp;
	int		i;

	while (lst->type != END)
	{
		if (before(lst) && space(lst->next))
		{
			tmp = ft_strdup(lst->next->value);
			i = 0;
			while (lst->next->value[i] != '\0')
			{
				if (lst->next->value[i] == '~' && ishome(lst->next->value, i))
				{
					free(lst->next->value);
					lst->next->value = add_home(home, tmp);
					tmp = ft_strdup(lst->next->value);
					i = 0;
				}
				else
					i++;
			}
			free(tmp);
		}
		lst = lst->next;
	}
}

void	expand_home(t_shell *shell, t_token *lst)
{
	char	*home;

	home = get_env_value(shell->var_env, "HOME");
	if (!home)
		return (home_not_set(shell));
	else
		replace_home(lst, home);
}
