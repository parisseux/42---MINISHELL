#include "../inc/minishell.h"

void	exit_command(t_token *lst_token, t_shell *shell, char *input)
{
	printf("exit\n");
	if (lst_token->next->value)
	{
		if (!ft_str_digit(lst_token->next->value))
			printf("minishell: exit: %s: numeric argument required\n", lst_token->next->value);
	}
	free_token_list(lst_token);
	ft_free_char_tab(shell->var_env);
	free(input);
	g_exit_status = 0;
	exit (0);
}
