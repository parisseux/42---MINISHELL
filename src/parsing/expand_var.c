#include "../inc/minishell.h"

char	*dolar_sign(char **line)
{
	char		*name;
	size_t		i;

	i = 0;
	(*line)++;
	if (ft_strlen(*line) == 0)
		return (NULL);
	name = NULL;
	if (**line == '?' || **line == '$' || **line == '0')
		return (name);
	while (ft_isalnum((*line)[i]) || (*line)[i] == '_')
        i++;
    if (i == 0)
        return (NULL);
	else
		name = ft_substr(*line, 0, i);
	return (name);
}

char	*find_pid()
{
	int		 fd;
	char	*name;
	char	**tab;

	fd = open("/proc/self/stat", O_RDONLY);
	if (fd <= 0)
		return (NULL);
	name = get_next_line(fd);
	if (!name)
		return (NULL);
	tab = ft_split(name, ' ');
	if (!tab)
		return (NULL);
	return (ft_strdup(tab[4]));
}

char	*dolar_special_cases(char **line, char *linee, t_shell *shell)
{
	char	*name;
	char	*token;

	name = NULL;
	token = NULL;
	if (**line != '?' && **line != '$' && **line != '0')
		return (linee);
	if (**line == '?')
		name = ft_itoa(shell->exit);
	else if (**line == '$')
		name = find_pid();
	else if (**line == '0')
		name = ft_strdup("minishell");
	if (name != NULL)
	{
		token = add_special_case(name, linee);
		return (token);
	}
	else
		return (NULL);
	return (name);
}

char	*find_var(t_shell *shell, char *name, char *value2)
{
	int		i;
	int		len;
	char	*tmp;

	i = 0;
	tmp = NULL;
	len = alphanum_len(name);
	while (shell->var_env[i])
	{
		if (!ft_varcmp(shell->var_env[i], name, len))
		{
			tmp = add(shell->var_env[i], value2, len + 1, '$');
			return (tmp);
		}
		i++;
	}
	i = 0;
	if (shell->shell_env != NULL)
	{
		while (shell->shell_env[i])
		{
			if (!ft_varcmp(shell->shell_env[i], name, len))
			{
				tmp = add(shell->shell_env[i], value2, len + 1, '$');
				return (tmp);
			}
			i++;
		}
	}
	tmp = rm_var(value2);
	return (tmp);
}

void	look_for_dolls(t_token *lst_token, t_shell *shell)
{
	char	*name;
	char	*value;
	char	*value2;

	name = NULL;
	while (lst_token != NULL && lst_token->type != END)
	{
		value = ft_strdup(lst_token->value);
		value2 = ft_strdup(lst_token->value);
		while (*value)
		{
			if (lst_token->type != WORD && lst_token->type != DQUOTE && lst_token->type != DEF)
				break ;
			if (*value == '$' && *value + 1 != ' ')
			{
				name = dolar_sign(&value);
				if (name)
				{
					free(lst_token->value);
					lst_token->value = find_var(shell, name, value2);
					free(name);
				}
				else
				{
					free(lst_token->value);
					lst_token->value = dolar_special_cases(&value, value2, shell);
				}
				value2 = ft_strdup(lst_token->value);
			}
			value++;
		}
		lst_token = lst_token->next;
	}
}
