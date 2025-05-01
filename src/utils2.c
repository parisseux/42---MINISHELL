/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avarrett <avarrett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 16:26:37 by pchatagn          #+#    #+#             */
/*   Updated: 2025/05/01 17:11:31 by avarrett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	free_token_list(t_token *lst_token)
{
	t_token	*tmp;

	while (lst_token)
	{
		tmp = lst_token;
		lst_token = lst_token->next;
		free(tmp->value);
		free(tmp);
	}
}

void	msg_error(char *msg, t_token *lst_token)
{
	printf("Error: %s\n", msg);
	free_token_list(lst_token);
}

char	*env_value(t_shell *shell, char **env, char *key)
{
	int	i;
	int	len;

	len = ft_strlen(key);
	i = 0;
	while (env[i])
	{
		if ((ft_strncmp(env[i], key, len) == 0 && env[i][len] == '='))
		{
			return (env[i] + len + 1);
		}
		i++;
	}
	if (!ft_strncmp(key, "HOME", 4))
		return (home_not_set(shell), NULL);
	return (NULL);
}

void	cleanup_readline(void)
{
	rl_free_line_state();
	rl_clear_history();
	rl_deprep_terminal();
}
