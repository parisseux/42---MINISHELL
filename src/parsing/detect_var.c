#include "../inc/minishell.h"

int	removing(int *i, int *j, char **input, char **cleaned)
{
	int	size;

	size = 0;
	size = closed_quotes(*input, (*input)[*i], *i);
	if (size == -1)
		return (quote_msg(*input[*i]), 0);
	(*i)++;
	while (size-- > 0)
		(*cleaned)[(*j)++] = (*input)[(*i)++];
	(*i)++;
	return (1);
}

char	*rm_quotes(char *input)
{
	char	*cleaned;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!ft_strchr(input, '\'') && !ft_strchr(input, '"'))
		return (input);
	cleaned = malloc((ft_strlen(input) + 1) * sizeof(char));
	if (!cleaned)
		return (NULL);
	while (input[i] != '\0')
	{
		if (input[i] == '\'' || input[i] == '"')
		{
			if (removing(&i, &j, &input, &cleaned) < 0)
				return (free(input), free(cleaned), NULL);
		}
		else
			cleaned[j++] = input[i++];
	}
	cleaned[j] = '\0';
	return (free(input), cleaned);
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

int	valid_token_var(char c, char *str)
{
	if (c == '\0')
		return (0);
	if (c == ' ' && !in_quote(c, str))
		return (0);
	if (ft_strchr("|<>", c) && !in_quote(c, str))
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
	while (valid_token_var(**input, copy))
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
	free(new);
	new = NULL;
	if (!new_token)
		return (NULL);
	return (new_token);
}
