/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_var_utils2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchatagn <pchatagn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 17:15:29 by pchatagn          #+#    #+#             */
/*   Updated: 2025/05/05 14:50:06 by pchatagn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	handle_valid_token(t_token *lst_token, t_shell *shell)
{
	t_token	*next;
	int		type;
	int		space;

	next = lst_token->next;
	type = lst_token->type;
	space = lst_token->space;
	which(&lst_token->value, shell);
	lst_token->next = next;
	lst_token->type = type;
	lst_token->space = space;
}

int	spe_case(char *value, int type, int space)
{
	if (!ft_strncmp(value, "$", 2) && (type == SQUOTE
			|| type == DQUOTE) && space == 0)
		return (1);
	return (0);
}

char	*get_exit_code(t_shell *shell)
{
	if (g_last_signal != 0)
		return (ft_itoa(g_last_signal));
	else
		return (ft_itoa(shell->exit));
}
