/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tolower.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avarrett <avarrett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 15:43:44 by avarrett          #+#    #+#             */
/*   Updated: 2024/10/10 16:56:59 by avarrett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_tolower(int a)
{
	if (a >= 65 && a <= 90)
		return (a + 32);
	return (a);
}

// #include <stdio.h>
// int main(void)
// {
// 	int a = 78;
// 	printf("%c", ft_tolower(a));
// 	return (0);
// }
