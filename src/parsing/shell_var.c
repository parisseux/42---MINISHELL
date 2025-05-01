/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_var.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avarrett <avarrett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 16:26:16 by pchatagn          #+#    #+#             */
/*   Updated: 2025/05/01 17:27:13 by avarrett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	prep_var_shell(char ***var)
{
	if (var == NULL)
		return ;
	*var = (char **)malloc(sizeof(char *) * 2);
	if (!*var)
		return ;
	(*var)[0] = ft_strdup("");
	if (!(*var)[0])
	{
		free(*var);
		return ;
	}
	(*var)[1] = NULL;
}

int	len_var(char *value)
{
	int	i;

	i = 0;
	while (value[i] != '\0')
	{
		if (value[i] == '=')
			return (i);
		i++;
	}
	return (-1);
}

int	shell_var(t_token *lst_token, t_shell *shell)
{
	t_token	*tmp;

	tmp = lst_token;
	if (is_pipe(lst_token))
		return (0);
	while (tmp->type != END)
	{
		if (tmp->type == DEF)
		{
			if (good_varname(tmp->value, '='))
				return (0);
			if (found_in_tab(shell->venv, tmp->value, len_var(tmp->value)))
			{
				if (shell->shell_env == NULL)
					prep_var_shell(&shell->shell_env);
				shell->shell_env = add_var_to_env(shell->shell_env, tmp->value);
			}
		}
		tmp = tmp->next;
	}
	return (0);
}
