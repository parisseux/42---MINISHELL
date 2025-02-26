/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ninisse <ninisse@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 14:39:51 by avarrett          #+#    #+#             */
/*   Updated: 2025/02/17 18:01:19 by ninisse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dest, const char *src, size_t size)
{
	size_t	i;

	i = ft_strlen(src);
	if (i + 1 < size)
		ft_memcpy(dest, src, i + 1);
	else if (size != 0)
	{
		ft_memcpy(dest, src, size - 1);
		dest[size - 1] = '\0';
	}
	return (i);
}

// #include <stdio.h>
// int main(void)
// {
// 	char b[] = "anabanana";
// 	char *a;

// 	a = malloc(9);
// 	printf("%zu", ft_strlcpy(a, b, 10));
// 	printf("\n%s", a);
// }