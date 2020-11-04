/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnoaille <lnoaille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/27 18:51:03 by lnoaille          #+#    #+#             */
/*   Updated: 2020/05/13 18:06:02 by lnoaille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_atoi(const char *str)
{
	int count;
	int neg;
	int number;

	number = 0;
	neg = 1;
	count = 0;
	while (str[count] == ' ' || str[count] == '\f' || str[count] == '\n'
	|| str[count] == '\r' || str[count] == '\v' || str[count] == '\t')
		count++;
	if (str[count] == '-' || str[count] == '+')
	{
		if (str[count] == '-')
			neg = -1;
		count++;
	}
	while ('0' <= str[count] && str[count] <= '9' && str[count])
	{
		number = number * 10 + (str[count] - '0');
		count++;
	}
	return (number * neg);
}
