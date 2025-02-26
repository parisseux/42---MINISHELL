/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avarrett <avarrett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 10:00:13 by gregorykoll       #+#    #+#             */
/*   Updated: 2024/10/15 14:17:06 by avarrett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *str, int c)
{
	char	a;
	int		i;
	int		l;
	int		check;

	i = 0;
	l = 0;
	check = -1;
	a = (char) c;
	while (str[i])
	{
		if (str[i] == a)
		{
			l = i;
			check = 1;
		}
		i++;
	}
	if (str[i] == a)
		return ((char *)&str[i]);
	if (check > 0)
		return ((char *)&str[l]);
	return (0);
}

// #include <stdio.h>
// int main(void)
// {
// 	const char str[80] = "hellolana";
// 	char a = 'l';
// 	printf("%s", ft_strrchr(str, a));
// 	return (0);
// }