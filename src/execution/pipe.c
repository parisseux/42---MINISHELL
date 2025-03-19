#include "../inc/minishell.h"

//dup2(old_fd, new_fd);

void handle_first_cmd(t_token *lst_token, t_shell *shell, int pipefd[][2], int n_pipes)
{
    close(pipefd[0][0]);
    dup2(pipefd[0][1], STDOUT_FILENO);
    close(pipefd[0][1]);
    (void)lst_token;
    (void)shell;
    (void)pipefd;
    (void)n_pipes;

}


void handle_last_cmd(t_token *lst_token, t_shell *shell, int pipefd[][2], int n_pipes)
{
    close(pipefd[n_pipes - 1][1]);
    dup2(pipefd[n_pipes - 1][0], STDIN_FILENO);
    close(pipefd[n_pipes - 1][0]);
        (void)lst_token;
    (void)shell;
    (void)pipefd;
    (void)n_pipes;
}

// handle_middle_cmd(lst_token, shell, i, pipefd);