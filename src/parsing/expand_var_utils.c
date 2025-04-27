#include "../inc/minishell.h"

char	*add_special_case(char *name, char *line)
{
	char	*tmp;
	int		size;
	int		i;
	int		j;

	i = 0;
	size = (ft_strlen(line) - 2) + ft_strlen(name);
	tmp = malloc((size + 1) * sizeof(char));
	while (line[i] != '$')
		i++;
	ft_strlcpy(tmp, line, i + 1);
	j = 0;
	while (name[j] != '\0')
	{
		tmp[j + i] = name[j];
		j++;
	}
	while (line[i + 2] != '\0')
	{
		tmp[i + j] = line[i + 2];
		i++;
	}
	tmp[i + j] = '\0';
	return (tmp);
}

int	malloc_size(char *new_value, char *value, int name_len)
{
	int	size;
	int	i;

	i = 0;
	size = 0;
	while (value[i] != '$' && value[i] != '\0')
		i++;
	size += i;
	size += ft_strlen(new_value + name_len);
	size += ft_strlen(value + i + name_len);
	return (size);
}

char	*add(char *new, char *value, int len)
{
	int		size;
	char	*tmp;
	int		i;
	size_t	j;

	i = 0;
	if (!value)
		return (NULL);
	size = malloc_size(new, value, len);
	tmp = malloc(size + 1 * sizeof(char));
	if (!tmp)
		return (NULL);
	ft_memset(tmp, 0, size + 1);
	while (value[i] != '$' && value[i] != '\0')
		i++;
	ft_strlcpy(tmp, value, i + 1);
	j = len + i;
	while (new[len] != '\0')
		tmp[i++] = new[len++];
	if (j < ft_strlen(value))
		ft_strlcat(tmp, value + j, size + 1);
	return (tmp);
}

char	*rm_var(char *value, int name_len)
{
	int		i;
	size_t	j;
	int		size;
	char	*new_value;

	i = 0;
	size = ft_strlen(value) - name_len;
	if (size <= 0)
		return (ft_strdup(""));
	new_value = malloc(size + 1 * sizeof(char));
	if (!new_value)
		return (ft_strdup(""));
	while (value[i] != '$' && value[i] != '\0')
		i++;
	ft_strlcpy(new_value, value, i + 1);
	j = name_len + i;
	if (j < ft_strlen(value))
		ft_strlcat(new_value, value + j, size + 1);
	return (new_value);
}

int	alphanum_len(char *value)
{
	int	i;

	i = 0;
	while (ft_isalnum(value[i]) || value[i] == '_')
		i++;
	return (i);
}
