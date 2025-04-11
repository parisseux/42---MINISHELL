#include "../inc/minishell.h"
 void sigint_handler(int sig)
{
    (void)sig;
    write(STDOUT_FILENO, "\n", 1);
    rl_on_new_line();
    rl_replace_line("", 0);
    rl_redisplay();
}

/*
 * Exemple de fonction générique pour installer un handler via sigaction
 */
 void set_signal_handler(int signo, void (*handler)(int), int flags)
{
    struct sigaction sa;

    sa.sa_handler = handler;
    sigemptyset(&sa.sa_mask);
    /*
     * SA_RESTART : si un appel système est interrompu par ce signal,
     * il est automatiquement relancé (read, write, etc.).
     * On peut mettre 0 si on veut un comportement strict sans relance.
     */
    sa.sa_flags = flags;

    if (sigaction(signo, &sa, NULL) < 0)
        perror("sigaction");
}

/*
 * Initialisation des signaux dans le parent :
 *  - SIGINT -> sigint_handler()
 *  - SIGQUIT -> ignoré
 */
void init_signals(void)
{
    set_signal_handler(SIGINT, sigint_handler, SA_RESTART);

    // Pour ignorer un signal avec sigaction, on met le handler à SIG_IGN
    set_signal_handler(SIGQUIT, SIG_IGN, 0);
}

/*
 * Restaure les signaux à leur comportement par défaut
 *  - typiquement appelé juste avant d'exécuter un programme externe (fork/exec)
 *  - ou lorsque vous voulez rétablir le comportement standard
 */
void restore_signals(void)
{
    set_signal_handler(SIGINT, SIG_DFL, 0);
    set_signal_handler(SIGQUIT, SIG_DFL, 0);
}

/*
 * Exemples si vous voulez un comportement spécifique pour SIGINT/SIGQUIT
 * dans un "non builtin", par exemple pour afficher un message spécifique.
 * Ici, on fait un handler spécial pour SIGINT et SIGQUIT
 * (vous pouvez bien sûr le personnaliser).
 */
 void sigint_handler_nb(int sig)
{
    (void)sig;
    write(STDOUT_FILENO, "\n", 1);
    rl_on_new_line();
    rl_replace_line("", 0);
    rl_redisplay();
}

 void sigquit_handler_nb(int sig)
{
    (void)sig;
    write(STDOUT_FILENO, "\n", 1);
}

/*
 * Pour installer ces handlers spécifiques (dans un contexte "non builtin")
 */
void non_builtin_signal(void)
{
    set_signal_handler(SIGINT, sigint_handler_nb, SA_RESTART);
    set_signal_handler(SIGQUIT, sigquit_handler_nb, 0);
}