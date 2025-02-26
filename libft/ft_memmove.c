/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avarrett <avarrett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 13:33:16 by gregorykoll       #+#    #+#             */
/*   Updated: 2024/10/15 13:40:40 by avarrett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t size)
{
	char	*destination;
	char	*source;
	size_t	i;

	if (!dest && !src)
		return (NULL);
	destination = (char *)dest;
	source = (char *)src;
	i = 0;
	if (destination > source)
	{
		while (size-- > 0)
			destination[size] = source[size];
	}
	else
	{
		while (i < size)
		{
			destination[i] = source[i];
			i++;
		}
	}
	return (dest);
}

// #include <stdio.h>
// #include <string.h>
// int main(void)
// {
// //    char str[90] = "aabbcc";
// //    printf("The string: %s\n", str);
// //    ft_memmove(str + 2, str, 4);
// //    printf( "New string: %s\n", str );
//    char str[90] = "memmove can be very useful......";
//    printf( "The string: %s\n", str );
//    printf( "The string: %s\n", str );
//    ft_memmove(str+20,str+15,11);
//    memmove(str+20,str+15,11);
//    printf( "New string: %s\n", str );
//    printf( "The string: %s\n", str );
//    return (0);
// }