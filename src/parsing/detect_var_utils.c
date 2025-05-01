/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   detect_var_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchatagn <pchatagn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 16:25:03 by pchatagn          #+#    #+#             */
/*   Updated: 2025/05/01 16:25:04 by pchatagn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	not_cmd(t_token *lst_token)
{
	t_token	*tmp;

	tmp = lst_token;
	if (lst_token == NULL)
		return (0);
	if (!ft_strncmp(tmp->value, "echo", 4))
		return (1);
	else if (!ft_strncmp(tmp->value, "cd", 3))
		return (1);
	else if (!ft_strncmp(tmp->value, "pwd", 4))
		return (1);
	else if (!ft_strncmp(tmp->value, "unset", 5))
		return (1);
	else if (!ft_strncmp(tmp->value, "env", 4))
		return (1);
	else if (!ft_strncmp(tmp->value, "exit", 6))
		return (1);
	else if (!ft_strncmp(tmp->value, "ls", 3))
		return (1);
	else if (!ft_strncmp(tmp->value, "cat", 4))
		return (1);
	return (0);
}

void	quote_msg(char c)
{
	write (STDERR_FILENO, "Unclosed ", 9);
	if (c == '\'')
		write (STDERR_FILENO, "single", 6);
	else
		write (STDERR_FILENO, "double", 6);
	write (STDERR_FILENO, " quotes\n", 8);
}

int	closed_quotes(char *copy, char quote, int i)
{
	int	len;

	len = 0;
	i++;
	while (copy[i] != '\0')
	{
		if (copy[i] == quote)
			return (len);
		i++;
		len++;
	}
	return (-1);
}

int	detect_var(char *input)
{
	int	check;

	check = 0;
	while (*input != ' ' && *input != '\0')
	{
		if (*input == '=')
			check = 1;
		input++;
	}
	if (check)
		return (1);
	return (0);
}
