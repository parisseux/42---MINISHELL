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
	}
}

void	find_var(t_shell *shell, char *name, char **value, int len)
{
	int		i;
	char	*tmp;
	char	*tmp2;

	i = 0;
	tmp = ft_strdup(*value);
	if (!tmp)
		return ;
	while (shell->var_env[i])
	{
		if (!ft_varcmp(shell->var_env[i], name, len))
		{
			free(value);
			tmp2 = add(shell->var_env[i], tmp, len + 1);
			*value = ft_strdup(tmp2);
			free(tmp);
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
				free(*value);
				tmp2 = add(shell->shell_env[i], tmp, len + 1);
				*value = tmp2;
				free(tmp);
			}
			i++;
		}
	}
	else
	{
		free(*value);
		tmp2 = rm_var(tmp, len + 1);
		*value = tmp2;
		free(tmp);
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
		if (dup[i] == '$')
		{
			name = dolar_sign(dup, i + 1);
			if (name)
			{
				find_var(shell, name, value, ft_strlen(name));
				free(name);
				dup = *value;
				i = 0;
			}
			else
				dol_spec_cases(value, i + 1, dup, shell);
		}
		i++;
	}
}

int	isvalid(int type, char *str)
{
	if (type != WORD || type != DQUOTE || type != DEF)
		return (0);

	while (*str != '\0')
	{
		if (*str == '$' && (*(str + 1) == '\0' || *(str + 1) == ' '))
		{
			ft_putstr_fd ("ok", 1);
			return (0);
		}			
	}
	return (1);
}

void	look_for_dolls(t_token *lst_token, t_shell *shell)
{
	int		type;
	int		space;

	type = 0;
	space = 0;
	while (lst_token != NULL && lst_token->type != END)
	{
		if (ft_strchr(lst_token->value, '$') && isvalid(lst_token->type, lst_token->value))
		{
			type = lst_token->type;
			space = lst_token->space;
			which(&lst_token->value, shell);
			lst_token->type = type;
			lst_token->space = space;			
		}
		else
			lst_token = lst_token->next;
	}
}
