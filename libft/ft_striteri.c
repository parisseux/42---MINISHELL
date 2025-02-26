/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avarrett <avarrett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 16:40:21 by avarrett          #+#    #+#             */
/*   Updated: 2024/10/10 16:56:10 by avarrett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_striteri(char *s, void (*f)(unsigned int, char*))
{
	int	i;

	i = 0;
	while (s[i])
	{
		f(i, &s[i]);
		i++;
	}
}

// #include <stdio.h>
// void my_function(unsigned int index, char *c)
// {
// 	if (index % 2 == 0 && *c >= 'a' && *c <= 'z')
// 		*c = *c - 32;;
// }
// int main(void)
// {
// 	char s[] = "anais";
// 	ft_striteri(s, my_function);
// 	printf("%s\n", s);
// 	return (0);
// }