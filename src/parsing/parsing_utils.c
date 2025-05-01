/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchatagn <pchatagn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 16:26:06 by pchatagn          #+#    #+#             */
/*   Updated: 2025/05/01 17:21:35 by pchatagn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	skip_space(char **input)
{
	int	i;

	i = 0;
	while (**input == ' ' || **input == '\t' || **input == '\v'
		|| **input == '\r' || **input == '\n' || **input == '\f')
	{
		(*input)++;
		i++;
	}
	if (i > 0)
		return (1);
	return (0);
}

t_token	*parse_pipe(char **input)
{
	(*input)++;
	return (create_token("|", PIPE, -1));
}

int	spaces(char input)
{
	if (input == ' ' || input == '\t' || input == '\v'
		|| input == '\r' || input == '\n' || input == '\f')
		return (1);
	return (0);
}
