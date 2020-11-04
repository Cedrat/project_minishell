/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnoaille <lnoaille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/05 16:34:00 by lnoaille          #+#    #+#             */
/*   Updated: 2020/11/04 18:16:18 by lnoaille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../header/libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	unsigned int divider;
	unsigned int nb2;
	unsigned int abs_nb;

	divider = 1;
	if (n < 0)
	{
		abs_nb = -n;
		ft_putchar_fd('-', fd);
	}
	else
		abs_nb = n;
	nb2 = abs_nb;
	while (nb2 > 9)
	{
		divider = divider * 10;
		nb2 = nb2 / 10;
	}
	while (divider)
	{
		ft_putchar_fd((abs_nb / divider) + '0', fd);
		abs_nb = abs_nb % divider;
		divider = divider / 10;
	}
}
