/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avarrett <avarrett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 13:26:59 by avarrett          #+#    #+#             */
/*   Updated: 2025/01/28 11:28:46 by avarrett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_fin(const char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

size_t	ft_strlen(const char *s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

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

char	*ft_strdup(const char *src)
{
	int		i;
	char	*cpy;

	i = 0;
	if (!src)
		return (NULL);
	cpy = (char *)malloc((ft_strlen(src) + 1) * sizeof(char));
	if (!cpy)
		return (NULL);
	while (src[i])
	{
		cpy[i] = src[i];
		i++;
	}
	cpy[i] = '\0';
	return (cpy);
}

char	*ft_strchr(const char *s, int c)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == c)
			return ((char *)&s[i]);
		i++;
	}
	return (0);
}

// int main(void)
// {
// 	FILE *test;
// 	char *ligne;
// 	int fd;
// 	test = fopen("test.txt", "w");
// 	fprintf(test, "J'espere,\nque ca fonctionne.\n hehe");
// 	fclose(test);
// 	test = fopen("test.txt", "r");
// 	fd = fileno(test);
// 	// ft_printf("%s", get_next_line(fd));
// 	while ((ligne = get_next_line(fd)) != NULL)
//     {
//         ft_printf("%s", ligne);  // Afficher la ligne
//         free(ligne);          // Libérer la mémoire allouée pour la ligne
//     }
// 	return (0);
// }
