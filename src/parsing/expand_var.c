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
	printf("%ld", ft_strlen(*line));
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

void	look_for_dolls(t_token *lst_token)
{
	t_token *tmp;
	char	*name;
	char	*value;

	name = NULL;
	tmp = lst_token;
	while (tmp)
	{
		value = ft_strdup(tmp->value);
		while (*value)
		{
			if (*value == '$')
			{
				printf("variable\n");
				name = dolar_sign(&value);
				if (!name)
					name = dolar_special_cases(&value);
				printf("named variable\n");
			}
			(*value)++;
		}
		tmp = tmp->next;
	}
	if (name)
		printf("%s\n", name);
	else
		printf("feinte\n");
	free(name);}
