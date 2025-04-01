#include "../inc/minishell.h"

t_token	*create_token(char *value, t_token_type type)
{
	t_token	*new_token;

	new_token = (t_token *)malloc(sizeof(t_token));
	if (!new_token)
		return (NULL);
	new_token->value = ft_strdup(value);
	new_token->type = type;
	new_token->next = NULL;
	return (new_token);
}

t_token	*extract_s_quote(char **input)
{
	t_token	*new_token;
	char	*value;
	char	*start;
	int		len;
	int		closed;

	closed = 0;
	(*input)++;
	start = *input;
	while (**input != '\'' && **input)
		(*input)++;
	if (**input == '\'')
		closed = 1;
	if (!closed)
		return (NULL);
	len = *input - start;
	value = (char *)malloc(sizeof(char) * (len + 1));
	if (!value)
		return (NULL);
	ft_strlcpy(value, start, len + 1);
	(*input)++;
	new_token = create_token(value, SQUOTE);
	free(value);
	return (new_token);
}

t_token	*extract_d_quote(char **input)
{
	t_token	*new_token;
	char	*value;
	char	*start;
	int		len;
	int		closed;

	closed = 0;
	(*input)++;
	start = *input;
	while (**input != '"' && **input)
		(*input)++;
	if (**input == '"')
		closed = 1;
	if (!closed)
		return (NULL);
	len = *input - start;
	value = (char *)malloc(sizeof(char) * (len + 1));
	if (!value)
		return (NULL);
	ft_strlcpy(value, start, len + 1);
	(*input)++;
	new_token = create_token(value, DQUOTE);
	free(value);
	return (new_token);
}

t_token	*ext_word(char **input)
{
	t_token	*new_token;
	char	*start;
	char	*value;
	int		len;

	start = *input;
	while (**input && !ft_strchr("|<> \'\"", **input) && !spaces(**input))
		(*input)++;
	len = ft_strlen(*input) - ft_strlen(start);
	len *= -1;
	if (len == 0)
		return (NULL);
	value = (char *)malloc(sizeof(char) * (len + 1));
	if (!value)
		return (NULL);
	ft_strlcpy(value, start, len + 1);
	new_token = create_token(value, WORD);
	free(value);
	return (new_token);
}
