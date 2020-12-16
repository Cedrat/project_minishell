/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_count_this_char.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnoaille <lnoaille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/12 14:08:33 by lnoaille          #+#    #+#             */
/*   Updated: 2020/12/15 17:08:39 by lnoaille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

size_t	ft_count_this_char(char *str, char letter)
{
	size_t i;

	i = 0;
	while (*str)
	{
		if (*str == letter)
			i++;
		str++;
	}
	return (i);
}
