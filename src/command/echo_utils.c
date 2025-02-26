/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avarrett <avarrett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 14:41:07 by parissachat       #+#    #+#             */
/*   Updated: 2025/02/25 12:21:39 by avarrett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	echo_dolar_sign(char **line)
{
	(*line)++;
	if (!ft_isalnum(**line) && **line != '_' && **line != '?' && **line != '$' && **line != '0')
	{
		printf("$");
		return ;
	}
	if (**line == '?' || **line == '$' || **line == '0')
	{
		dolar_special_cases(line);
		return ;
	}
	dolar_expand_variable(line);
}

void	dolar_expand_variable(char **line)
{
	char	name[100];
	char	*var;
	int		i;

	i = 0;
	while (ft_isalnum(**line) || **line == '_')
	{
		name[i] = **line;
		i++;
		(*line)++;
	}
	name[i] = '\0';
	var = getenv(name);
	if (var)
		printf("%s", var);
}

void	dolar_special_cases(char **line)
{
	if (**line == '?')
	{
		printf("%d", g_exit_status);
		(*line)++;
		return ;
	}
	else if (**line == '$')
	{
		printf("%d", getpid());
		(*line)++;
		return ;
	}
	else if (**line == '0')
	{
		printf("./minishell");
		(*line)++;
		return ;
	}
}

int	echo_check_n_flag(char **line)
{
	int	n_flag;

	n_flag = 0;
	while (**line == '-' && *((*line) + 1) == 'n')
	{
		(*line) += 2;
		n_flag = 1;
	}
	return (n_flag);
}
