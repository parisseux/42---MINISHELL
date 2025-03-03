/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchatagn <pchatagn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 13:56:07 by pchatagn          #+#    #+#             */
/*   Updated: 2025/03/03 14:27:41 by pchatagn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	g_exit_status = 0;

void    execute_minishell(t_shell *shell, char *input)
{
    t_token *lst_token;
	
	lst_token = NULL;
    lst_token = tokenisation(input);
	if (!lst_token)
	{
		printf("Error: tokenisation failed\n");
		return ;
	}
	printf("Token list:\n");
	print_token_list(lst_token);
	if (check_syntax_error(lst_token))
		return ;
	execution(lst_token, shell);
	easy_command(lst_token, shell);
	printf("end\n");
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
	shell.var_env = setup_minishell(env);
	if (!shell.var_env)
		return (1);
	while (1)
	{
		input = readline("\033[35mminishell$ \033[0m");
		if (!input)
			break ;
		if (input)
			add_history(input);
		if (ft_strlen(input) > 0)
			execute_minishell(&shell, input);
		free(input);
	}
	ft_free_char_tab(shell.var_env);
	return (0);
}
