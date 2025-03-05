#include "../inc/minishell.h"

char	*dolar_sign(char **line)
{
	char	*name;
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

char	*dolar_special_cases(char **line)
{
	char	*name;

	name = NULL;
	if (ft_strlen(*line) == 0)
		return (NULL);
	if (**line == '?')
		name = ft_itoa(g_exit_status);
	else if (**line == '$')
		name = ft_itoa(getpid());
	else if (**line == '0')
		name = ft_strdup("minishell");
	return (name);
}

char	*add(char *new_value, char *value, int name_len)
{
	char *tmp;
	int i;
	int j;

	i = 0;
	j = 0;
	tmp = ft_strdup("");
	while (value[i] != '$')
	{
		tmp[i] = value[i];
		i++; 
	}
	j = name_len + i;
	if (value[i] == '$')
	{
		name_len++;
		while (new_value[name_len] != '\0')
		{
			printf("tmp = %s\n", tmp);
			tmp[i] = new_value[name_len];
			i++;
			name_len++;
		}
	}
	j++;
	while (value[j + i] != '\0')
	{
		tmp[i] = value[j];
		i++;
		j++;
	}
	tmp[i] = '\0';
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
	j = i;
	j++;
	while (ft_isalnum(value[j]) || value[j] == '_')
		j++;
	while (value[j] != '\0')
	{
		new_value[i] = value[j];
		i++;
		j++;
	}
	new_value[i + 1] = '\0';
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
			tmp = add(shell->var_env[i], value2, len);
		}
		i++;
	}
	if (!check)
		tmp = rm_var(value2);
	printf("tmp avant d'envoyer dans lookfordolls= %s\n", tmp);
	return (tmp);
}

void	look_for_dolls(t_token *lst_token, t_shell *shell)
{
	char	*name;
	char	*value;
	char 	*value2;

	name = NULL;
	while (lst_token != NULL)
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
					lst_token->value = find_var(shell, name, value2);
				else
					lst_token->value = dolar_special_cases(&value);
				printf("lst_token->value dans lookfordolls= %s\n", lst_token->value);
			}
			value++;
		}
		lst_token = lst_token->next;
	}
}

