/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_toupper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avarrett <avarrett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 15:36:30 by avarrett          #+#    #+#             */
/*   Updated: 2024/10/10 16:57:11 by avarrett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_toupper(int a)
{
	if (a >= 97 && a <= 122)
		return (a - 32);
	return (a);
}

// #include <stdio.h>

// int main(void)
// {
// 	int a = 98;
// 	printf("%c", ft_toupper(a));
// 	return (0);
// }