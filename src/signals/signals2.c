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

char	*find_pid()
{
	int		 fd;
	char	*name;
	char	**tab;

	fd = open("/proc/self/stat", O_RDONLY);
	if (fd <= 0)
		return (NULL);
	name = get_next_line(fd);
	if (!name)
		return (NULL);
	tab = ft_split(name, ' ');
	if (!tab)
		return (NULL);
	return (ft_strdup(tab[4]));
}