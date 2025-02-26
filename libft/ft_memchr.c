/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avarrett <avarrett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 14:51:26 by gregorykoll       #+#    #+#             */
/*   Updated: 2024/10/17 15:54:56 by avarrett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *str, int lettre, size_t count)
{
	unsigned char	ch;
	unsigned char	*string;
	size_t			i;

	string = (unsigned char *)str;
	ch = lettre;
	i = 0;
	while (i < count)
	{
		if (string[i] == ch)
			return ((char *)&string[i]);
		i++;
	}
	return (0);
}

// #include <stdio.h>
// int main(void)
// {
// 	const char str[80] = "helloana";
//     char *str2 = (char *)ft_memchr(str, 'a', 18);
//     printf("%s", str2);
// 	return (0);
// }