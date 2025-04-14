#include "../inc/minishell.h"

int	g_stop = 0;

int	start_minishell(t_shell *shell, char *input)
{
	t_token	*lst_token;

	lst_token = NULL;
	lst_token = tokenisation(input);
	if (!lst_token)
	{
		free(input);
		return (1);
	}
	if (lst_token->type == END)
		return (0);
	look_for_dolls(lst_token, shell);
	if (ft_strncmp(lst_token->value, "export", 7))
		shell->exit = shell_var(lst_token, shell);
	expand_home(shell, lst_token);
	if (check_syntax_error(lst_token))
	{
		shell->exit = 2;
		return (1);
	}
	execution(lst_token, shell);
	free_token_list(lst_token);
	return (0);
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
	init_signals();
	shell.var_env = setup_minishell(env);
	if (!shell.var_env)
		return (1);
	shell.shell_env = NULL;
	shell.exit = 0;
	input = NULL;
	while (1)
	{
		if (isatty(fileno(stdin)))
			input = readline("minishell$ ");
		else
		{
			char *line;
			line = get_next_line(fileno(stdin));
			input = ft_strtrim(line, "\n");
			free(line);
		}
		if (!input)
			break ;
		add_history(input);
		start_minishell(&shell, input);
		free(input);
	}
	//clean_exit(shell.exit, NULL, shell.var_env, shell.shell_env);
	return (0);
}
