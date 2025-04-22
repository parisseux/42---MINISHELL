#include "../inc/minishell.h"

int	detect_var(char *input)
{
	int	check;

	check = 0;
	while (*input != ' ' && *input != '\0')
	{
		if (*input == '=')
			check = 1;
		input++;
	}
	if (check)
		return (1);
	return (0);
}

int	closed_quotes(char *copy, char quote, int i)
{
	int	len;

	len = 0;
	i++;
	while (copy[i] != '\0')
	{
		if (copy[i] == quote)
			return (len);
		i++;
		len++;
	}
	return (-1);
}

char	*rm_quotes(char *input)
{
	char	*cleaned;
	int		size;
	int		i;
	int		j;

	i = 0;
	size = 0;
	j = 0;
	if (!ft_strchr(input, '\'') && !ft_strchr(input, '"'))
		return (input);
	cleaned = ft_strdup("");
	while (input[i] != '\0')
	{
		if (input[i] == '\'' || input[i] == '"')
		{
			size = closed_quotes(input, input[i], i);
			if (size == -1)
			{
				free(cleaned);
				free(input);
				return (NULL);
			}
			i++;
			while (size > 0)
			{
				cleaned[j] = input[i];
				j++;
				i++;
				size--;
			}
			i++;
		}
		else
			cleaned[j++] = input[i++];
	}
	cleaned[j] = '\0';
	free(input);
	return (cleaned);
}

int	in_quote(char pipe_or_else, char *input)
{
	int	single_q;
	int	double_q;

	single_q = 0;
	double_q = 0;
	while (*input != '\0')
	{
		if (*input == pipe_or_else)
		{
			if (single_q % 2 == 0 && double_q % 2 == 0)
				return (0);
		}
		else if (*input == '\'')
			single_q++;
		else if (*input == '"')
			double_q++;
		input++;
	}
	if (single_q % 2 != 0 && double_q % 2 != 0)
		return (0);
	return (1);
}

t_token	*token_var(char **input)
{
	t_token	*new_token;
	char	*copy;
	char	*new;
	int		len;

	len = 0;
	copy = ft_strdup(*input);
	while ((**input != ' ' || in_quote(**input, copy))
		&& (!ft_strchr("|<>", **input)
			|| in_quote(**input, copy)) && **input != '\0')
	{
		len++;
		(*input)++;
	}
	copy[len] = '\0';
	new = rm_quotes(copy);
	if (!new)
		new_token = NULL;
	else if (!good_varname(new, '='))
		new_token = create_token(new, DEF);
	else
		new_token = create_token(new, WORD);
	new = NULL;
	if (!new_token)
		return (NULL);
	return (new_token);
}
