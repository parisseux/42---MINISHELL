/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchatagn <pchatagn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 16:26:31 by pchatagn          #+#    #+#             */
/*   Updated: 2025/05/01 17:16:12 by pchatagn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

volatile sig_atomic_t	g_last_signal = 0;

int	start_minishell(t_shell *shell, char *input)
{
	t_token	*lst_token;

	lst_token = NULL;
	lst_token = tokenisation(input);
	if (!lst_token)
		return (1);
	if (lst_token->type == END)
	{
		free_token_list(lst_token);
		return (0);
	}
	look_for_dolls(lst_token, shell);
	if (in_shell_env(lst_token))
		shell->exit = shell_var(lst_token, shell);
	replace_home(shell, lst_token);
	if (check_syntax_error(lst_token))
	{
		shell->exit = 2;
		free_token_list(lst_token);
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

int	init_minishell(char **env, t_shell *shell, char **input)
{
	init_parent_signals();
	if (*env == NULL)
		prep_var_shell(&shell->var_env);
	else
		shell->var_env = setup_minishell(env);
	if (!shell->var_env)
		return (1);
	shell->shell_env = NULL;
	shell->exit = 0;
	*input = NULL;
	return (0);
}

int	main(int ac, char **av, char **env)
{
	char	*input;
	t_shell	shell;

	(void)ac;
	(void)av;
	if (init_minishell(env, &shell, &input))
		return (1);
	while (1)
	{
		if (isatty(STDIN_FILENO))
		{
			input = readline("minishell$ ");
			if (!input)
				break ;
		}
		else
			return (1);
		add_history(input);
		start_minishell(&shell, input);
		free(input);
	}
	cleanup_readline();
	clean_exit(shell.exit, NULL, shell.var_env, shell.shell_env);
	return (0);
}
