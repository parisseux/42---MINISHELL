#include "../inc/minishell.h"

void    sigint_handler_heredoc(int sig)
{
    (void)sig;
    //write(STDOUT_FILENO, "\n", 1);
    // rl_on_new_line();
	// rl_replace_line("", 0);
	// rl_redisplay();
    g_stop = 1;
}
void signals_heredoc(void)
{
	signal(SIGQUIT, SIG_IGN);
}