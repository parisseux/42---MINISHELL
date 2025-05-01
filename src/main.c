/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avarrett <avarrett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 16:26:31 by pchatagn          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2025/05/01 17:27:13 by avarrett         ###   ########.fr       */
=======
/*   Updated: 2025/05/01 17:16:12 by pchatagn         ###   ########.fr       */
>>>>>>> 5216c54ba3fb0e17a3a74fd94726e920d158e3e1
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
<<<<<<< HEAD
	init_parent_signals();
	if (*env == NULL)
		prep_var_shell(&shell.venv);
	else
		shell.venv = setup_minishell(env);
	if (!shell.venv)
=======
	if (init_minishell(env, &shell, &input))
>>>>>>> 5216c54ba3fb0e17a3a74fd94726e920d158e3e1
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
	clean_exit(shell.exit, NULL, shell.venv, shell.shell_env);
	return (0);
}
