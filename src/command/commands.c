
#include "../inc/minishell.h"

// void	easy_command(t_token *lst_token, t_shell *shell)
// {
// 	t_file	*file;
// 	file = NULL;
// 	if (print_or_file(lst_token))
// 		file = open_file(lst_token, print_or_file(lst_token));
// 	if (lst_token->type == 0)
// 	{
// 		if(!ft_strncmp(lst_token->value, "env", 4))
// 			env_command(shell, lst_token, file);
// 		else if(!ft_strncmp(lst_token->value, "pwd", 4))
// 			pwd_command(file);
// 		else if (!ft_strncmp(lst_token->value, "echo", 5))
// 		{
// 			if (lst_token->next->type == 8)
// 				printf("\n");
// 			else if (!ft_strncmp(lst_token->next->value, "-n", 2))
// 				echo_command(lst_token->next->next, 1, file);
// 			else
// 				echo_command(lst_token->next, 0, file);
// 		}
// 		else if (!ft_strncmp(lst_token->value, "export", 7))
// 			export_command(lst_token, shell);
// 		else
// 		{
// 			printf("%s: command not found\n", lst_token->value);
// 			g_exit_status = 127;
// 		}	
// 	}
// 	if (print_or_file(lst_token))
// 		fclose(file->file);
// }
