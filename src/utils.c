#include "../inc/minishell.h"

void	free_token_list(t_token *lst_token)
{
	t_token	*tmp;

	while (lst_token)
	{
		tmp = lst_token;
		lst_token = lst_token->next;
		free(tmp->value);
		free(tmp);
	}
}

void	msg_error(char *msg, t_token *lst_token)
{
	printf("Error: %s\n", msg);
	free_token_list(lst_token);
}

void	cmd_err(char *msg, char *cmd, int exit, t_shell *shell)
{
	write (STDOUT_FILENO, "minishell: ", 11);
	write (STDOUT_FILENO, cmd, ft_strlen(cmd));
	write (STDOUT_FILENO, msg, ft_strlen(msg));
	write (STDERR_FILENO, "\n", 1);
	shell->exit = exit;
}

void	ft_free_char_tab(char **tab)
{
	int	i;

	i = 0;
	if (!tab)
		return ;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

int	ft_varcmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	if (!s1 && !s2)
		return (0);
	while (i < n && (s2[i] || s1[i]))
	{
		if ((unsigned char) s1[i] == (unsigned char) s2[i])
			i++;
		else
			return ((unsigned char) s1[i] - (unsigned char) s2[i]);
	}
	if (s1[i] != '=')
		return (1);
	return (0);
}

void	clean_exit(int exit_status, t_token *lst_token, char **env, char **shell)
{
	clear_history();
	if (env)
		ft_free_char_tab(env);
	if (shell)
		ft_free_char_tab(shell);
	if (lst_token)
		free_token_list(lst_token);
	exit(exit_status);
}
