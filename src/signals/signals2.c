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
