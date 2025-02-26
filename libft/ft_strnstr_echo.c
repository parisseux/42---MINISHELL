/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr_echo.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchatagn <pchatagn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 11:55:52 by ninisse           #+#    #+#             */
/*   Updated: 2025/02/11 13:59:09 by pchatagn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr_echo(const char *foin, const char *aiguille, size_t a)
{
	size_t	i;
	size_t	j;
	size_t	complet;

	j = 0;
	i = 0;
	complet = ft_strlen(aiguille);
	if (complet == 0)
		return ((char *)foin);
	while (foin[i] && i < a)
	{
		j = 0;
		while (foin[i + j] == aiguille[j] && (i + j < a))
		{
			if (j == complet)
				return ((char *)&foin[j]);
			j++;
		}
		if (j == complet)
			return ((char *)&foin[j]);
		i++;
	}
	return (0);
}
