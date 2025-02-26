/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avarrett <avarrett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 17:04:08 by avarrett          #+#    #+#             */
/*   Updated: 2024/10/17 15:55:37 by avarrett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	char	nbr;

	nbr = n + '0';
	if (n == -2147483648)
		write (fd, "-2147483648", 11);
	else if (n == 2147483647)
		write (fd, "2147483647", 10);
	else if (n >= 0)
	{
		if (n < 10)
			write (fd, &nbr, 1);
		else if (n >= 10)
		{
			ft_putnbr_fd(n / 10, fd);
			ft_putnbr_fd(n % 10, fd);
		}
	}
	else if (n < 0)
	{
		write (fd, "-", 1);
		ft_putnbr_fd(n *= -1, fd);
	}
}

// int main(void)
// {
// 	ft_putnbr_fd(-975100, 1);
// 	return (0);
// }