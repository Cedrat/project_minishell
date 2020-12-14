/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_split_arg.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnoaille <lnoaille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/10 03:06:45 by lnoaille          #+#    #+#             */
/*   Updated: 2020/12/14 16:08:20 by lnoaille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"


static void insert_tab(size_t *l, size_t p, char **new_tab, char **str)
{
	while (str[*l])
	{
		new_tab[p + *l] = ft_strdup(str[*l]);
		(*l)++;
	}
	(*l)--;
}

char **add_split_arg(char **tab, int *i)
{
	char **str;
	char **new_tab;
 	size_t p;
	size_t l;

	str = ft_split(tab[*i], ' ');
	p = tab_range(str);
	l = tab_range(tab);
	new_tab = malloc(sizeof(char *) * (p + l + 1));
	p = 0;
	l = 0;
	while(tab[p])
	{
		if (p == *i)
			insert_tab(&l, p, new_tab, str);
		else
			new_tab[p + l] = ft_strdup(tab[p]);
		p++;
	}
	ft_free_tab(tab);
	ft_free_tab(str);
	new_tab[p + l] = NULL;
	*i = *i + l;
	return (new_tab);
}
