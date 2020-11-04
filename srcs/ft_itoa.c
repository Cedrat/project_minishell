/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnoaille <lnoaille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/04 17:23:50 by lnoaille          #+#    #+#             */
/*   Updated: 2020/11/04 18:16:45 by lnoaille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../header/libft.h"

static	int		ft_lenint(long int n)
{
	long int	divider;
	int			i;

	i = 0;
	divider = 1;
	while (divider * 10 <= n || divider * 10 <= -n)
	{
		divider = divider * 10;
		i++;
	}
	if (n < 0)
	{
		i++;
	}
	return (i + 1);
}

static	int		ft_poweroften(long int n)
{
	long int divider;

	divider = 1;
	while (n)
	{
		divider = divider * 10;
		n--;
	}
	return (divider / 10);
}

char			*ft_itoa(int n)
{
	char		*tab;
	int			i;
	long int	divider;
	long int	nb;

	nb = n;
	i = 0;
	if (!(tab = malloc(sizeof(char) * (ft_lenint(n) + 1))))
		return (0);
	if (n < 0)
	{
		tab[i] = '-';
		nb = -nb;
		i++;
	}
	divider = ft_poweroften(ft_lenint(nb));
	while (divider)
	{
		tab[i] = ((nb / divider) + '0');
		nb = nb % divider;
		divider = divider / 10;
		i++;
	}
	tab[i] = '\0';
	return (tab);
}
