#include "../inc/minishell.h"

char	*dolar_sign(char *line, int index)
{
	char		*name;
	size_t		i;

	i = 0;
	name = NULL;
	if (line[index] == '?' || line[index] == '$'
		|| line[index] == '0' || line[index] == '\0')
		return (NULL);
	i = alphanum_len(line + index);
	if (i > 0)
		name = ft_substr(line, index, i);
	else
		return (NULL);
	return (name);
}

void	dol_spec_cases(char **value, int index,
	char *line, t_shell *shell)
{
	char	*name;
	char	*tmp;
	char	*cpy;

	name = NULL;
	tmp = NULL;
	if (line[index] != '?' && line[index] != '$' && line[index] != '0')
		return ;
	cpy = ft_strdup(*value);
	if (!cpy)
		return ;
	if (line[index] == '?')
		name = ft_itoa(shell->exit);
	else if (line[index] == '$')
		name = ft_itoa(getpid());
	else if (line[index] == '0')
		name = ft_strdup("minishell");
	if (name)
	{
		free(*value);
		tmp = add_special_case(name, cpy);
		*value = tmp;
		free(cpy);
		free(name);
	}
}

void	find_var(t_shell *shell, char *name, char **value, int len)
{
	int		i;
	char	*tmp;
	char	*tmp2;

	i = 0;
	if (!*value)
		return ;
	tmp = ft_strdup(*value);
	if (!tmp)
		return ;
	while (shell->var_env[i])
	{
		if (!ft_varcmp(shell->var_env[i], name, len))
		{
			tmp2 = add(shell->var_env[i], tmp, len + 1);
			free(*value);
			*value = tmp2;
			return ;
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
				tmp2 = add(shell->shell_env[i], tmp, len + 1);
				free(*value);
				*value = tmp2;
				return ;
			}
			i++;
		}
	}
	else
	{
		tmp2 = rm_var(tmp, len + 1);
		free(*value);
		*value = tmp2;
		free(tmp);
		return ;
	}
}

void	which(char **value, t_shell *shell)
{
	char	*name;
	char	*dup;
	int		i;

	i = 0;
	name = NULL;
	dup = *value;
	while (dup[i] != '\0')
	{
		if (dup[i] == '$' && dup[i + 1] != ' ')
		{
			name = dolar_sign(dup, i + 1);
			if (name)
			{
				find_var(shell, name, value, ft_strlen(name));
				free(name);
				if (!*value)
					return ;
			}
			else
				dol_spec_cases(value, i + 1, dup, shell);
			dup = *value;
			i = 0;
		}
		if (dup[i] != '\0')
			i++;
	}
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
	if (after[1] == ' ' || after[1] == '\0')
		return (0);
	return (1);
}

void	look_for_dolls(t_token *lst_token, t_shell *shell)
{
	int		type;
	int		space;
	t_token	*next;

	type = 0;
	space = 0;
	while (lst_token != NULL && lst_token->type != END)
	{
		if (isvalid(lst_token->type, lst_token->value) > 0)
		{
			next = lst_token->next;
			type = lst_token->type;
			space = lst_token->space;
			which(&lst_token->value, shell);
			lst_token->next = next;
			lst_token->type = type;
			lst_token->space = space;
		}
		else
			lst_token = lst_token->next;
	}
}
