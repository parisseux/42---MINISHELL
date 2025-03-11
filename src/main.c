
#include "../inc/minishell.h"

//permet de gerer CTR - C
void	sigint_handler(int sig)
{
	(void)sig;
    write(1, "\n", 1);
    rl_on_new_line();
    rl_replace_line("", 0);
    rl_redisplay();  
}

//parsing de l'input, separation en token, expansion variable, sytnhaxx error, et lancement de l'execution
void	start_minishell(t_shell *shell, char *input)
{
	t_token	*lst_token;

	lst_token = NULL;
	lst_token = tokenisation(input);
	if (!lst_token)
	{
		printf("Error: tokenisation failed\n");
		clean_exit(EXIT_SUCCESS, NULL, shell->var_env);
	}
	look_for_dolls(lst_token, shell);
	if (check_syntax_error(lst_token))
		return ;
	execution(lst_token, shell);
}

//faire une copie de env dans une structure appeler shell
char	**setup_minishell(char **env)
{
	char	**var_env;
	int		i;

	i = 0;
	while (env[i])
		i++;
	var_env = (char **)malloc(sizeof(char *) * (i + 1));
	if (!var_env)
		return (NULL);
	i = 0;
	while (env[i])
	{
		var_env[i] = ft_strdup(env[i]);
		i++;
	}
	var_env[i] = 0;
	return (var_env);
}

int	main(int ac, char **av, char **env)
{
	char	*input;
	t_shell	shell;

	(void)ac;
	(void)av;
	signal(SIGINT, sigint_handler);
    signal(SIGQUIT, SIG_IGN);
	shell.var_env = setup_minishell(env);
	if (!shell.var_env)
		return (1);
	shell.exit = 0;
	input = NULL;
	while (1)
	{
		input = readline("\033[35mminishell$ \033[0m");
		if (!input)
			break ;
		else
			add_history(input);
		start_minishell(&shell, input);
		free(input);
	}
	clean_exit(EXIT_SUCCESS, NULL, shell.var_env);
	return (0);
}
