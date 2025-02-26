/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avarrett <avarrett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 14:31:55 by avarrett          #+#    #+#             */
/*   Updated: 2024/10/17 15:54:50 by avarrett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_space(int n)
{
	int	nb;

	nb = 1;
	if (n < 0)
	{
		nb++;
		n *= -1;
	}
	while (n >= 10)
	{
		nb++;
		n /= 10;
	}
	return (nb);
}

char	*ft_putnbr(int n, char *s, int i)
{
	if (n >= 0)
	{
		while (i >= 0)
		{
			s[i] = (n % 10) + '0';
			n /= 10;
			i--;
		}
	}
	else if (n < 0)
	{
		n *= -1;
		s[0] = '-';
		while (i > 0)
		{
			s[i] = (n % 10) + '0';
			n /= 10;
			i--;
		}
	}
	return (s);
}

static char	*int_min_chaine(char *s)
{
	s[0] = '-';
	s[1] = '2';
	s[2] = '1';
	s[3] = '4';
	s[4] = '7';
	s[5] = '4';
	s[6] = '8';
	s[7] = '3';
	s[8] = '6';
	s[9] = '4';
	s[10] = '8';
	s[11] = '\0';
	return (s);
}

char	*ft_itoa(int n)
{
	char	*s;
	int		i;
	int		taille;

	if (n == -2147483648)
	{
		s = (char *)malloc((11 + 1) * sizeof(char));
		if (s == 0)
			return (NULL);
		s = (char *)int_min_chaine(s);
	}
	else
	{
		taille = ft_space(n);
		s = (char *)malloc((taille + 1) * sizeof(char));
		if (s == 0)
			return (NULL);
		i = taille - 1;
		s = (char *)ft_putnbr(n, s, i);
		while (i < taille)
			i++;
		s[i] = '\0';
	}
	return (s);
}

// #include <stdio.h>
// int main(void)
// {
// 	printf("%s", ft_itoa(-2147483648));
// 	return (0);
// }