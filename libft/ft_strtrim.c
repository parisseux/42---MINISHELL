/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avarrett <avarrett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 11:33:52 by avarrett          #+#    #+#             */
/*   Updated: 2024/10/17 15:54:14 by avarrett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	trim_ou_pas(char lettre_s, char const *set)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if (lettre_s == set[i])
			return (0);
		i++;
	}
	return (1);
}

static char	*ft_strcpy(char const *src, size_t a)
{
	size_t	i;
	char	*ptn_de_mot;

	i = 0;
	if (a <= 0)
		return (ft_strdup(""));
	ptn_de_mot = (char *)malloc((a + 1) * sizeof(char));
	if (!ptn_de_mot)
		return (NULL);
	while (i < a)
	{
		ptn_de_mot[i] = src[i];
		i++;
	}
	ptn_de_mot[i] = '\0';
	return (ptn_de_mot);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		i;
	int		j;

	i = 0;
	j = ft_strlen(s1) - 1;
	if (!s1)
		return (ft_strdup(""));
	while (trim_ou_pas(s1[i], set) != 1)
		i++;
	while (j >= i && trim_ou_pas(s1[j], set) != 1)
		j--;
	if (i > j)
		return (ft_strdup(""));
	return (ft_strcpy(s1 + i, j - i + 1));
}

// #include <stdio.h>
// int main(void)
// {
// 	const char s1[] = "";
// 	const char s2[] = "";
// 	char *new;
// 	new = (char *)ft_strtrim(s1, s2);
// 	printf("%s", new);
// 	free(new);
// 	return (0);
// }