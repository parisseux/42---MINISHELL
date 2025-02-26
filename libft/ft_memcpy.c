/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avarrett <avarrett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 11:05:38 by gregorykoll       #+#    #+#             */
/*   Updated: 2024/10/17 15:55:02 by avarrett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t size)
{
	unsigned char	*destination;
	unsigned char	*source;
	size_t			i;

	destination = (unsigned char *)dest;
	source = (unsigned char *)src;
	i = 0;
	if (!dest && !src)
		return (NULL);
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
	return (destination);
}

// #include <stdio.h>
// #include <string.h>
// int main() 
// {
// 	char first_str[100] = "Hello World!";
// 	char second_str[100] = "Welcome to Tutorialspoint";
// 	printf("The Actual Statements:-\n");
// 	printf("first_str: %s\n", first_str);
// 	printf("second_str: %s\n", second_str);
// 	//copying all bytes of second_str to first_str
// 	ft_memcpy(first_str, second_str, strlen(second_str));
// 	printf("After executing the function memcpy()\n");
// 	printf("first_str: %s\n", first_str);
// 	printf("second_str: %s\n", second_str);
// 	return 0;
// }