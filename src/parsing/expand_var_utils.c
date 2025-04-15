#include "../inc/minishell.h"

char	*add_special_case(char *name, char *line)
{
	char	*tmp;
	int		size;
	int		i;
	int		j;

	i = 0;
	j = ft_strlen(name);
	size = (ft_strlen(line) - 2) + ft_strlen(name);
	tmp = malloc(size * sizeof(char));
	while (line[i] != '$')
	{
		tmp[i] = line[i];
		i++;
	}
	ft_strcat(tmp, name);
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
	int	i;
	int	j;

	i = 0;
	while (value[i] != '$' && value[i] != '\0')
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
	int		size;
	char	*tmp;
	int		i;
	size_t	j;

	i = 0;
	size = malloc_size(new_value, value, name_len);
	tmp = malloc(size + 1 * sizeof(char));
	if (tmp == NULL)
		return (NULL);
	while (value[i] != '$' && value[i] != '\0')
		i++;
	ft_strlcpy(tmp, value, i + 1);
	j = name_len + i;
	while (new_value[name_len] != '\0' && tmp[i] != '\0') 
	{
		tmp[i] = new_value[name_len];
		i++;
		name_len++;
	}
	if (j >= ft_strlen(value))
	{
		tmp[i] = '\0';
		ft_putstr_fd(tmp, 1);
		return (tmp);
	}
	ft_strcat(tmp, value + j);
	return (tmp);
}

char	*rm_var(char *value, int name_len)
{
	int		i;
	int		j;
	int		size;
	char	*new_value;

	i = 0;
	size = ft_strlen(value) - name_len;
	new_value = malloc(size + 1 * sizeof(char));
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
