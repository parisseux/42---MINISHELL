/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avarrett <avarrett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 09:58:03 by avarrett          #+#    #+#             */
/*   Updated: 2024/10/17 15:54:19 by avarrett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char			*new_s;
	size_t			i;

	i = 0;
	if (!s)
		return (NULL);
	if (ft_strlen(s) < start)
		return (ft_strdup(""));
	if (len > ft_strlen(s + start))
		len = ft_strlen(s + start);
	new_s = (char *)malloc((len + 1) * sizeof(char));
	if (new_s == 0)
		return (NULL);
	while (i < len)
	{
		new_s[i] = s[start];
		i++;
		start++;
	}
	new_s[i] = '\0';
	return (new_s);
}

// #include <stdio.h>
// int main(void)
// {
// 	char str[] = "coucou anais anais";
// 	char *new_s;
// 	unsigned int start = 7;
// 	size_t len = 10;
// 	new_s = (char *)ft_substr(str, start, len);
// 	printf("%s", new_s);
// 	free(new_s);
// 	return (0);
// }