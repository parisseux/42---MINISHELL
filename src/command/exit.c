#include "../inc/minishell.h"

//A orriger pour gerer correcter les STDOUT
//on ne peut pas faire comme ca car ne fonction pas thr
//ex: exit >> lala devrait crer le ficher lala et la ca met 
// numeric argument required
void	exit_command(t_token *lst_token, t_shell *shell, char *input)
{
	int	i;

	i = 0;
	write(STDOUT_FILENO, "exit\n", 5);
	if (lst_token->next->value)
	{
		if (!ft_str_digit(lst_token->next->value))
		{
			i = ft_strlen(lst_token->next->value);
			write(STDOUT_FILENO, "minishell: exit: ", 17);
			write(STDOUT_FILENO, lst_token->next->value, i);
			write(STDOUT_FILENO, ": numeric argument required\n", 28);
		}
	}
	free_token_list(lst_token);
	ft_free_char_tab(shell->var_env);
	if (input != NULL)
		free(input);
	shell->exit = 0;
	exit (0);
}
