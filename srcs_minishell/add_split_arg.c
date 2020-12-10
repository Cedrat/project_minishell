/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_split_arg.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnoaille <lnoaille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/10 03:06:45 by lnoaille          #+#    #+#             */
/*   Updated: 2020/12/10 03:37:37 by lnoaille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

char **add_split_arg(char **tab, int *i)
{
	char **str;
	char **new_tab;
	int p;
	int l;

	p = 0;
	l = 0;
	str = ft_split(tab[*i], ' ');
	while(str[p])
		p++;
	while(tab[l])
		l++;
	new_tab = malloc(sizeof(char *) * (p + l + 1));
	p = 0;
	l = 0;
	while(tab[p])
	{
		if (p == *i)
		{
			while (str[l])
			{
				new_tab[p + l] = ft_strdup(str[l]);
				l++;
			}
			l--;
		}
		else
		{
			new_tab[p + l] = ft_strdup(tab[p]);
		}
		p++;

	}
	ft_free_tab(tab);
	ft_free_tab(str);
	new_tab[p + l] = NULL;
	*i = *i + l;

	return (new_tab);
}
