/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_charispresent.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnoaille <lnoaille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/04 18:49:51 by lnoaille          #+#    #+#             */
/*   Updated: 2020/11/16 17:28:11 by lnoaille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

int		ft_charispresent(const char* str, char lett)
{
	while(*str)
	{
		if (*str == lett)
			return (1);
		str++;
	}
	return (0);
}
