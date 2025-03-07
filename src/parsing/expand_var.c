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


char	*add_special_case(char *name, char *line)
{
	char	*tmp;
	int		i;
	int		ok;
	int		size;
	int		j;

	i = 0;
	ok = ft_strlen(name);
	size = (ft_strlen(line) - 2) + ft_strlen(name);
	tmp = malloc(size * sizeof(char));
	while (line[i] != '$')
	{
		tmp[i] = line[i];
		i++;
	}
	j = 0;
	while (name[j] != '\0')
	{
		printf("%s\n", tmp);
		tmp[i + j] = name[j];
		j++;
	}
	while (line[i + 2] != '\0')
	{
		tmp[i + ok] = line[i + 2];
		i++;
	}
	tmp[i + ok] = '\0';
	printf("%s\n", tmp);
	return (tmp);
}

char	*dolar_special_cases(char **line, char *linee, t_shell *shell)
{
	char	*name;
	char	*token;

	name = NULL;
	token = NULL;
	if (ft_strlen(*line) == 0)
		return (NULL);
	if (**line == '?')
		name = ft_itoa(shell->exit);
	else if (**line == '$')
		name = ft_itoa(getpid());
	else if (**line == '0')
		name = ft_strdup("minishell");
	if (name)
	{
		printf("name = %s\n", name);
		printf("line= %s\n", linee);
		token = add_special_case(name, linee);
		printf("token in specase %s\n", token);
		return (token);
	}
	return (name);
}


int		jpp(char *new_value, char *value, int name_len)
{ 
	int i;
	int j;

	i = 0;
	while (value[i] != '$')
		i++; 
	j = name_len + i;
	if (value[i] == '$')
	{
		name_len++;
		while (new_value[name_len] != '\0')
		{
			i++;
			name_len++;
		}
	}
	j++;
	while (value[j] != '\0')
	{
		i++;
		j++;
	}
	return (i);
}

char	*add(char *new_value, char *value, int name_len)
{
	char *tmp;
	int i;
	int	j;
	int size;

	i = 0;
	size = jpp(new_value, value, name_len);
	tmp = malloc(size * sizeof(char));
	if (!tmp)
		return (NULL);
	while (value[i] != '$' && value[i] != '\0')
	{
		tmp[i] = value[i];
		i++; 
	}
	j = name_len + i;
	if (value[i] == '$')
	{
		while (new_value[name_len] != '\0')
		{
			tmp[i] = new_value[name_len];
			i++;
			name_len++;
		}
	}
	while (value[j] != '\0')
	{
		tmp[i] = value[j];
		j++;
		i++;
	}
	tmp[i] = '\0';
	free(value);
	return (tmp);
}

char *rm_var(char *value)
{
	int i;
	int j;
	char *new_value;

	i = 0;
	new_value = ft_strdup("");
	while (value[i] != '$')
	{
		new_value[i] = value[i];
		i++;
	}
	j = i + 1;
	while (ft_isalnum(value[j]) || value[j] == '_')
		j++;
	while (value[j] != '\0')
	{
		new_value[i] = value[j];
		i++;
		j++;
	}
	new_value[i + 1] = '\0';
	free(value);
	return (new_value);
}

int	alphanum_len(char *value)
{
	int i;

	i = 0;
	while (ft_isalnum(value[i]) || value[i] == '_')
		i++;
	return (i);
}

char	*find_var(t_shell *shell, char *name, char *value2)
{
	int i;
	int check;
	int len;
	char *tmp;

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
	printf("tmp avant d'envoyer dans lookfordolls= %s\n", tmp);
	free(name);
	return (tmp);
}

void	look_for_dolls(t_token *lst_token, t_shell *shell)
{
	char	*name;
	char	*value;
	char 	*value2;

	name = NULL;
	while (lst_token != NULL && lst_token->type != END)
	{
		value = ft_strdup(lst_token->value);
		value2 = ft_strdup(lst_token->value);
		while (*value)
		{
			if (*value == '$')
			{
				if (ft_strlen(value) == 1)
					break ;
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
				printf("lst_token->value dans lookfordolls= %s\n", lst_token->value);
			}
			value++;
		}
		lst_token = lst_token->next;
	}
}