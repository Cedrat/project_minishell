/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_divide_to_pipe.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnoaille <lnoaille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/20 16:27:35 by lnoaille          #+#    #+#             */
/*   Updated: 2020/11/20 17:22:36 by lnoaille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

char **ft_divide_to_pipe(char **split)
{
	char **new_tab;
	size_t i = 0;
	size_t p = 0;

	while(split[i])
	{
		if (!(ft_strcmp(split[i], "|")))
			p++;
		i++;
	}
	new_tab = malloc(sizeof(char *) * (p  + 2));
	i = 0;
	p = 0;
	new_tab[p] = malloc(1);
	new_tab[p][0] = '\0';
	while(split[i])
	{
		if (ft_strcmp(split[i], "|") != 0)
		{
			new_tab[p] = ft_strjoin(new_tab[p], split[i]);
			new_tab[p] = ft_strjoin(new_tab[p], " ");
		}
		else
		{
			p++;
			new_tab[p] = malloc(1);
			new_tab[p][0] = '\0';
		}
		i++;
	}
	new_tab[p + 1] = NULL;
	return (new_tab);
}
