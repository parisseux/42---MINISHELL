/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avarrett <avarrett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 16:22:01 by avarrett          #+#    #+#             */
/*   Updated: 2024/10/15 13:50:26 by avarrett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	char	a;
	int		i;

	i = 0;
	a = (char) c;
	while (s[i])
	{
		if (s[i] == a)
			return ((char *)&s[i]);
		i++;
	}
	if (s[i] == a)
		return ((char *)&s[i]);
	return (0);
}

// #include <stdio.h>
// int main(void)
// {
// 	const char str[80] = "helloana";
// 	char a = 'a';
// 	printf("%s", ft_strchr(str, a));
// 	return (0);
// }