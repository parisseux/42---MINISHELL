/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avarrett <avarrett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 16:26:31 by pchatagn          #+#    #+#             */
/*   Updated: 2025/05/01 17:27:13 by avarrett         ###   ########.fr       */
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
	char	**venv;
	int		i;

	i = 0;
	while (env[i])
		i++;
	venv = (char **)malloc(sizeof(char *) * (i + 1));
	if (!venv)
		return (NULL);
	i = 0;
	while (env[i])
	{
		venv[i] = ft_strdup(env[i]);
		i++;
	}
	venv[i] = 0;
	return (venv);
}

int	main(int ac, char **av, char **env)
{
	char	*input;
	char	*line;
	t_shell	shell;

	(void)ac;
	(void)av;
	init_parent_signals();
	if (*env == NULL)
		prep_var_shell(&shell.venv);
	else
		shell.venv = setup_minishell(env);
	if (!shell.venv)
		return (1);
	shell.shell_env = NULL;
	shell.exit = 0;
	input = NULL;
	while (1)
	{
		if (isatty(STDIN_FILENO))
		{
			input = readline("minishell$ ");
			if (!input)
				break ;
		}
		else
		{
			line = get_next_line(fileno(stdin));
			if (!line)
				break ;
			input = ft_strtrim(line, "\n");
			free(line);
			if (!input)
				break ;
		}
		if (!input)
			break ;
		if (*input)
			add_history(input);
		start_minishell(&shell, input);
		free(input);
	}
	cleanup_readline();
	clean_exit(shell.exit, NULL, shell.venv, shell.shell_env);
	return (0);
}
