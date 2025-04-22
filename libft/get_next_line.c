/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avarrett <avarrett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 12:03:56 by avarrett          #+#    #+#             */
/*   Updated: 2025/04/17 14:22:58 by avarrett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr_gnl(char const *s, unsigned int start, size_t len)
{
	char	*new_s;
	size_t	i;

	i = 0;
	if (!s)
		return (NULL);
	if (ft_strlen(s) < start)
		return (ft_strdup(""));
	if (len > ft_strlen(s + start))
		len = ft_strlen(s + start);
	new_s = (char *)malloc((len + 1) * sizeof(char));
	if (new_s == 0)
		return (NULL);
	while (i < len)
	{
		new_s[i] = s[start];
		i++;
		start++;
	}
	new_s[i] = '\0';
	return (new_s);
}

static char	*line_reader(int fd, char *reste, char *buff)
{
	ssize_t	check_read;
	char	*send_help;

	check_read = 1;
	while (check_read > 0)
	{
		check_read = read (fd, buff, BUFFER_SIZE);
		if (check_read == -1)
		{
			free(reste);
			return (NULL);
		}
		else if (check_read == 0)
			break ;
		buff[check_read] = '\0';
		if (!reste)
			reste = ft_strdup("");
		send_help = reste;
		reste = ft_strjoin(reste, buff);
		free(send_help);
		send_help = NULL;
		if (ft_strchr(buff, '\n'))
			break ;
	}
	return (reste);
}

static char	*line_cleaner(char *line)
{
	size_t	i;
	char	*new_reste;

	i = 0;
	while (line[i] && line[i] != '\n')
		i++;
	if (line[i] == 0)
		return (0);
	new_reste = ft_substr_gnl(line, i + 1, ft_strlen(line) - i);
	if (*new_reste == 0)
	{
		free(new_reste);
		return (NULL);
	}
	line [i + 1] = '\0';
	return (new_reste);
}

char	*get_next_line(int fd)
{
	static char	*reste;
	char		*nextline;
	char		*buff;

	buff = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buff)
		return (NULL);
	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
	{
		free(reste);
		reste = NULL;
		return (NULL);
	}
	nextline = line_reader(fd, reste, buff);
	free(buff);
	if (!nextline)
		return (NULL);
	reste = line_cleaner(nextline);
	return (nextline);
}
