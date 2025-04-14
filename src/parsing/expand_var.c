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
		if ((!ft_isalnum(**line)) && **line != '_')
			return (name);
		i++;
	}
	name = ft_strdup(*line);
	return (name);
}

char	*dol_spec_cases(char **line,
	char *linee, t_shell *shell)
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
	else
		tmp = rm_var(value2);
	return (tmp);
}

char	*which_doll(char *value, t_shell *shell)
{
	char	*name;
	char	*new;
	char	*dup;

	name = NULL;
	dup = ft_strdup(value);
	while (*value)
	{
		if (*value == '$')
		{
			name = dolar_sign(&value);
			if (name)
			{
				write (1, name, ft_strlen(name));
				new = find_var(shell, name, dup);
				free(name);
				write (1, "found\n", 6);
			}
			else
				new = dol_spec_cases(&value, dup, shell);
			free(dup);
			dup = ft_strdup(new);
		}
		value++;
	}
	
	free(dup);
	return (new);
}

void	look_for_dolls(t_token *lst_token, t_shell *shell)
{
	char	*value;
	char	*temp;

	while (lst_token != NULL && lst_token->type != END)
	{
		if (lst_token->type != WORD && lst_token->type != DQUOTE 
			&& lst_token->type != DEF)
			break ;
		if (ft_strchr(lst_token->value, '$'))
		{
			
			value = ft_strdup(lst_token->value);
			temp = which_doll(value, shell);
			
			free(lst_token->value);
			lst_token->value = ft_strdup(temp);
			free(value);			
		}
		lst_token = lst_token->next;
	}
}
