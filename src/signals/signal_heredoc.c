#include "../inc/minishell.h"

void    sigint_handler_heredoc(int sig)
{
    (void)sig;
    write(STDOUT_FILENO, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
    exit(130);
}
void signals_heredoc(void)
{
    signal(SIGINT, sigint_handler_heredoc);
	signal(SIGQUIT, SIG_IGN);
}