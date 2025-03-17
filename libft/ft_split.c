/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avarrett <avarrett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 13:17:37 by avarrett          #+#    #+#             */
/*   Updated: 2025/03/17 17:04:11 by avarrett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_occurence(char const *s, char c)
{
	int	i;
	int	compte;

	if (!s)
		return (0);
	i = 0;
	compte = 0;
	while (s[i])
	{
		while (s[i] == c)
			i++;
		if (s[i])
			compte++;
		while (s[i] && s[i] != c)
			i++;
	}
	return (compte);
}

static char	*ft_strcpy(char const *src, size_t a)
{
	size_t	i;
	char	*ptn_de_mot;

	i = 0;
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

char	**ft_split(char const *s, char c)
{
	size_t	end;
	int		len;
	size_t	start;
	char	**tab;

	end = 0;
	len = 0;
	tab = malloc((ft_occurence(s, c) + 1) * sizeof(char *));
	if (!tab)
		return (NULL);
	while (s[end])
	{
		while (s[end] == c)
			end++;
		start = end;
		while (s[end] != c && s[end])
			end++;
		if (end > start)
		{
			tab[len] = ft_strcpy(s + start, end - start);
			if (!tab[len++])
				return (ft_free_tab(tab, len), NULL);
		}
	}
	return (tab[len] = NULL, tab);
}

// #include <stdio.h>

// int main(void)
// {
// 	char const s[] = "  sp l it de merde";
// 	char sep = ' ';
// 	int i;
// 	char **tab;

// 	tab = ft_split(s, sep);
// 	i = 0;
// 	while (i < ft_occurence(s, sep))
// 	{
// 		printf("%s\n", tab[i]);
// 		i++;
// 	}
// 	ft_free(tab, ft_occurence(s, sep));
// 	return (0);
// }