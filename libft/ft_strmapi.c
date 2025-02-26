/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avarrett <avarrett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 16:02:34 by avarrett          #+#    #+#             */
/*   Updated: 2024/10/17 15:54:01 by avarrett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char	*new_s;
	size_t	taille;
	int		i;

	taille = ft_strlen(s);
	new_s = 0;
	i = 0;
	new_s = (char *)malloc((taille + 1) * sizeof(char));
	if (new_s == 0)
		return (NULL);
	while (s[i])
	{
		new_s[i] = f(i, s[i]);
		i++;
	}
	new_s[i] = '\0';
	return (new_s);
}

// #include <stdio.h>
// char my_function(unsigned int index, char c)
// {
// 	if (index % 2 == 0 && c >= 'a' && c <= 'z')
// 		return (c - 32);
// 	return (c);
// }
// int main(void)
// {
// 	char s[] = "anais";
// 	char *s2;
// 	s2 = ft_strmapi(s, my_function);
// 	printf("%s\n", s2);
// 	free(s2);
// 	return (0);
// }