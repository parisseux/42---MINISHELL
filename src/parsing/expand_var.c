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
		name = find_pid();
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
	tmp = *value;
	if (found_in_tab(shell->var_env, name, len) > 0)
	{
		i = found_in_tab(shell->var_env, name, len);
		tmp2 = add(shell->var_env[i], tmp, len + 1);
		free(*value);
		*value = tmp2;
		return ;
	}
	if (found_in_tab(shell->shell_env, name, len) > 0)
	{
		i = found_in_tab(shell->shell_env, name, len);
		tmp2 = add(shell->shell_env[i], tmp, len + 1);
		free(*value);
		*value = tmp2;
		return ;
	}
	tmp2 = rm_var(tmp, len + 1);
	free(*value);
	*value = tmp2;
}

void	which(char **value, t_shell *shell)
{
	char	*name;
	char	*dup;
	int		i;

	init(&i, &name, &dup, *value);
	while (dup[i] != '\0')
	{
		if (dup[i] == '$' && dup[i + 1] != ' ' && dup[i + 1] != '\0')
		{
			name = dolar_sign(dup, i + 1);
			if (name)
			{
				find_var(shell, name, value, ft_strlen(name));
				free(name);
				if (!*value || !ft_strncmp(*value, dup, ft_strlen(*value)))
					return ;
			}
			else
				dol_spec_cases(value, i + 1, dup, shell);
			init(&i, &name, &dup, *value);
		}
		if (dup[i] != '\0')
			i++;
	}
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
