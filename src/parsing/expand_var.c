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

char	*find_var(t_shell *shell, char *name, char *value)
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
			tmp = add(shell->var_env[i], value, len + 1);
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
				add(shell->shell_env[i], value, len + 1);
				return (tmp);
			}
			i++;
		}
	}
	else
		tmp = rm_var(value, len + 1);
	return (tmp);
}

char	*which_doll(char *value, t_shell *shell)
{
	char	*name;
	char	*temp;
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
				new = find_var(shell, name, dup);
				free(name);
			}
			else
				new = dol_spec_cases(&value, dup, shell);
			ft_putstr_fd(new, 1);
			temp = dup;
			dup = ft_strdup(new);
			free(temp);
			free(new);
		}
		value++;
	}
	return (dup);
}

int	isvalid(int type)
{
	if (type == WORD || type == DQUOTE || type == DEF)
		return (1);
	return (0);
}

void	look_for_dolls(t_token *lst_token, t_shell *shell)
{
	char	*value;
	char	*temp;

	value = NULL;
	temp = NULL;
	while (lst_token != NULL && lst_token->type != END)
	{
		if (ft_strchr(lst_token->value, '$') && isvalid(lst_token->type))
		{

			value = ft_strdup(lst_token->value);
			temp = which_doll(value, shell);
			ft_putstr_fd(temp, 1);
			free(lst_token->value);
			lst_token->value = temp;

			free(value);			
		}
		else
			lst_token = lst_token->next;
	}
}
