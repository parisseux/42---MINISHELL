/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avarrett <avarrett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 10:41:27 by avarrett          #+#    #+#             */
/*   Updated: 2024/10/17 15:53:45 by avarrett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		i;
	int		j;
	char	*mixmix;

	i = 0;
	j = 0;
	mixmix = (char *)malloc((ft_strlen(s1) + ft_strlen(s2) + 1) * sizeof(char));
	if (!mixmix)
		return (NULL);
	while (s1[i])
		mixmix[i++] = s1[j++];
	j = 0;
	while (s2[j])
	{
		mixmix[i] = s2[j];
		i++;
		j++;
	}
	mixmix[i] = '\0';
	return (mixmix);
}

// #include <stdio.h>

// int main(void)
// {
// 	const char s1[] = "coucou ";
// 	const char s2[] = "ca va ?";
// 	char *new;
// 	new = (char *)ft_strjoin(s1,s2);
// 	printf("%s", new);
// 	free(new);
// 	return (0);
// }