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
	{
		printf("1\n");
		return (name);
	}
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
	printf("len special case == %ld\n", ft_strlen(*line));
	if (ft_strlen(*line) == 0)
		return (NULL);
	if (**line == '?')
		name = ft_itoa(g_exit_status);
	else if (**line == '$')
		name = ft_itoa(getpid());
	else if (**line == '0')
		name = ft_strdup("minishell");
	printf("%s", name);
	return (name);
}

void	find_var(t_shell *shell, char *name, t_token *tmp)
{
	int i;
	int check;

	i = 0;
	check = 0;
	while (shell->var_env[i])
	{
		if (!ft_varcmp(shell->var_env[i], name, ft_strlen(name)))
		{
			tmp->value = ft_strdup(shell->var_env[i] + ft_strlen(name) + 1);
			check = 1;
		}
		i++;
	}
	if (!check)
	{
		tmp->value = ft_strdup("");
		if (tmp->next->type == 8)
			tmp->type = 8;
	}
}

void	look_for_dolls(t_token *lst_token, t_shell *shell)
{
	t_token *tmp;
	char	*name;
	char	*value;

	name = NULL;
	tmp = lst_token;
	while (tmp != NULL)
	{
		value = ft_strdup(tmp->value);
		while (*value)
		{
			if (*value == '$')
			{
				if (ft_strlen(value) == 1)
					break ;
				name = dolar_sign(&value);
				if (name)
					find_var(shell, name, tmp);
				else
					tmp->value = dolar_special_cases(&value);
			}
			value++;
		}
		tmp = tmp->next;
	}
	free(name);}
