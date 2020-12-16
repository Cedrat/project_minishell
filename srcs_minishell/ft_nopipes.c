/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nopipes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnoaille <lnoaille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/04 18:45:11 by lnoaille          #+#    #+#             */
/*   Updated: 2020/12/15 18:54:54 by lnoaille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

int	ft_nopipes(char **args)
{
	size_t i;

	i = 0;
	while (args[i])
	{
		if (ft_charispresent(args[i], '|'))
			return (0);
		i++;
	}
	return (1);
}
