/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tri_tab_str.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnoaille <lnoaille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/06 16:20:50 by lnoaille          #+#    #+#             */
/*   Updated: 2020/11/06 16:37:24 by lnoaille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

void ft_tri_tab_str(char** str)
{
	size_t		i;
	char	*old_value;

	i = 1;
	while (str[i])
	{
		if (ft_strcmp(str[i - 1], str[i]) > 0)
		{
			old_value = str[i - 1];
			str[i - 1] = str[i];
			str[i] = old_value;
			i = 1;
		}
		else
			i++;
	}
}
