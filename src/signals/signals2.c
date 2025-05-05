/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avarrett <avarrett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 18:15:50 by pchatagn          #+#    #+#             */
/*   Updated: 2025/05/05 15:35:31 by avarrett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	parent_sigint(int signo)
{
	(void)signo;
	g_last_signal = 130;
	write(STDOUT_FILENO, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

char	*find_pid(void)
{
	int		fd;
	char	*name;
	char	*line;
	char	**tab;

	fd = open("/proc/self/stat", O_RDONLY);
	if (fd < 0)
		return (NULL);
	line = get_next_line(fd);
	close(fd);
	if (!line)
		return (NULL);
	tab = ft_split(line, ' ');
	if (!tab)
		return (free(line), NULL);
	name = ft_strdup(tab[4]);
	return (free(line), ft_free_char_tab(tab), name);
}
