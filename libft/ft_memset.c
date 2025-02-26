/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avarrett <avarrett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 10:22:27 by gregorykoll       #+#    #+#             */
/*   Updated: 2024/10/17 15:55:06 by avarrett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *str, int charact, size_t count)
{
	unsigned char	*chaine;
	size_t			i;

	i = 0;
	chaine = (unsigned char *)str;
	while (i < count)
	{
		chaine[i] = (unsigned char)charact;
		i++;
	}
	return (chaine);
}

// #include <stdio.h>
// int main(void)
// {
//     char str[70] = "welcome to 42";
//     size_t count = 7;
//     int charact = 'x';
//     printf("%s\n", str);
//     ft_memset(str, charact, count);
//     printf("%s", str);
//     return (0);
// }