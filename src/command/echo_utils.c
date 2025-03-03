/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avarrett <avarrett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 14:41:07 by parissachat       #+#    #+#             */
/*   Updated: 2025/02/27 16:21:06 by avarrett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

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
