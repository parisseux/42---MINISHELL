#include "../inc/minishell.h"

void	sigint_handler(int sig)
{
	(void)sig;
	printf("\n\033[35mminishell$ \033[0m");
}

void	start_minishell(t_shell *shell, char *input)
{
	t_token	*lst_token;

	lst_token = NULL;
	lst_token = tokenisation(input);
	if (!lst_token)
	{
		printf("Error: tokenisation failed\n");
		return ;
	}
	look_for_dolls(lst_token, shell);
	if (!ft_strncmp(lst_token->value, "exit", 4))
		exit_command(lst_token, shell, input);
	if (check_syntax_error(lst_token))
		return ;
	execution(lst_token, shell);
	free_token_list(lst_token);
}

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
		{
			printf("exit\n");
			break ;
		}
		else
			add_history(input);
		if (ft_strlen(input) > 0)
			start_minishell(&shell, input);
		free(input);
	}
	ft_free_char_tab(shell.var_env);
	return (0);
}
