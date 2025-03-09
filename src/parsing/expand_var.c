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
	while (i <= ft_strlen(*line))
	{
		if ((!ft_isalnum(**line)))
			return (name);
		i++;
	}
	name = ft_strdup(*line);
	return (name);
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
		name = ft_itoa(getpid());
	else if (**line == '0')
		name = ft_strdup("minishell");
	if (name)
	{
		token = add_special_case(name, linee);
		return (token);
	}
	return (name);
}

char	*find_var(t_shell *shell, char *name, char *value2)
{
	int		i;
	int		check;
	int		len;
	char	*tmp;

	i = 0;
	check = 0;
	len = alphanum_len(name);
	while (shell->var_env[i])
	{
		if (!ft_varcmp(shell->var_env[i], name, len))
		{
			check = 1;
			tmp = add(shell->var_env[i], value2, len + 1);
		}
		i++;
	}
	if (!check)
		tmp = rm_var(value2);
	free(name);
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
			if (lst_token->type != WORD && lst_token->type != DQUOTE)
				break ;
			if (*value == '$')
			{
				name = dolar_sign(&value);
				if (name)
				{
					free(lst_token->value);
					lst_token->value = find_var(shell, name, value2);
				}
				else
				{
					free(lst_token->value);
					lst_token->value = dolar_special_cases(&value, value2, shell);
				}
			}
			value++;
		}
		lst_token = lst_token->next;
	}
}
