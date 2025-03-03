/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ninisse <ninisse@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 10:09:43 by gregorykoll       #+#    #+#             */
/*   Updated: 2025/03/03 12:50:40 by ninisse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	if (!s1 && !s2)
		return (0);
	while (i < n && (s2[i] || s1[i]))
	{
		if ((unsigned char) s1[i] == (unsigned char) s2[i])
			i++;
		else
			return ((unsigned char) s1[i] - (unsigned char) s2[i]);
	}
	return (0);
}

// #include <stdio.h>
// int main(void)
// {
//     const char s1[] = "coucou ana";
//     const char s2[] = "coubou";
//     size_t a = 2;
//     printf("%d", ft_strncmp(s1, s2, a));
//     return (0);
// }