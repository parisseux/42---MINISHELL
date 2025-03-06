#include "../inc/minishell.h"


//simple redirection au fonctions correpondantes aux buitltin
// void	exec_builtin_cmd(t_token *lst_token, t_shell *shell, t_file *file)
// {
// 	int redir;

// 	redir = is_redir(lst_token);
// 	if (redir)
// 		printf("redirection need to be handle\n");
// if (lst_token->type == 0)	
// 	{
// 		if (!ft_strncmp(lst_token->value, "env", 4))
// 			env_command(shell, lst_token, file);
// 		else if (!ft_strncmp(lst_token->value, "pwd", 4))
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
// 		else
// 		{
// 			printf("%s: command not found\n", lst_token->value);
// 			shell->exit = 127;
// 		}
// 	}
// 	if (print_or_file(lst_token))
// 		fclose(file->file);
// }

//attribution to the cmd echo, cd, pwd, export, unset, env, exit
//and if redierction fd_out is beinf passed to the cmd
//if no redirection fd = -1 
//builtin qui necessitent stdout: echo, pwd, export, env
//builtin  qui ncesstient stdin: aucune donc pas besoins de gere < et <<
//seul truc a gerer est si le file ou directory quil veut ouvrrir n'exsite pas alors rreur
void builtin_cmd(t_token *lst_token, t_shell *shell, int fd_out)
{
	t_token *temp;

	temp = lst_token;
	while (temp->type != END)
	{
		if (temp->type == WORD)
		{
			if (!ft_strncmp(temp->value, "env", 4))
			 	env_command(shell, lst_token, fd_out);
			else if (!ft_strncmp(temp->value, "pwd", 4))
			 	pwd_command(fd_out);
			// else if (!ft_strncmp(lst_token->value, "echo", 5))
			// {
			// 	if (lst_token->next->type == 8)
			// 		printf("\n");
			// 	else if (!ft_strncmp(lst_token->next->value, "-n", 2))
			// 		echo_command(lst_token->next->next, 1, file);
			// 	else
			// 		echo_command(lst_token->next, 0, file);
			// }
			// else
			// {
			// 	printf("%s: command not found\n", lst_token->value);
			// 	shell->exit = 127;
			// }
		}
		temp = temp->next;
	}
}