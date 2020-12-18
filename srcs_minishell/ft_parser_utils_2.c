/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser_utils_2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnoaille <lnoaille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/18 20:28:37 by lnoaille          #+#    #+#             */
/*   Updated: 2020/12/18 20:30:40 by lnoaille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

int	ft_count_doll(char *arg)
{
	int	count;
	int	i;

	i = 0;
	count = 0;
	while (arg[i])
	{
		if (arg[i] == '$')
			count++;
		i++;
	}
	return (count);
}
