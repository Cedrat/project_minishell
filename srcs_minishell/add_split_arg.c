/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_split_arg.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnoaille <lnoaille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/10 03:06:45 by lnoaille          #+#    #+#             */
/*   Updated: 2020/12/17 17:53:53 by lnoaille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

static	void	copy_tab(char **new_tab, char **tab, size_t p, size_t l)
{
	if ((new_tab[p + l] = ft_strdup(tab[p])) == NULL)
		exit(0);
}

static	char	**init_tab_with_two_tabs(char **new_tab, char **str,
												char **tab)
{
	size_t p;
	size_t l;

	p = tab_range(str);
	l = tab_range(tab);
	if ((new_tab = malloc(sizeof(char *) * (p + l + 1))) == NULL)
		exit(0);
	return (new_tab);
}

static	void	insert_tab(size_t *l, size_t p, char **new_tab, char **str)
{
	while (str[*l])
	{
		if ((new_tab[p + *l] = ft_strdup(str[*l])) == NULL)
			exit(0);
		(*l)++;
	}
	(*l)--;
}

char			**add_split_arg(char **tab, int *i)
{
	char	**str;
	char	**new_tab;
	size_t	p;
	size_t	l;

	p = 0;
	l = 0;
	if ((str = ft_split(tab[*i], ' ')) == NULL)
		exit(0);
	new_tab = NULL;
	new_tab = init_tab_with_two_tabs(new_tab, str, tab);
	while (tab[p])
	{
		if ((int)p == *i)
			insert_tab(&l, p, new_tab, str);
		else
			copy_tab(new_tab, tab, p, l);
		p++;
	}
	ft_free_tab(tab);
	ft_free_tab(str);
	new_tab[p + l] = NULL;
	*i = *i + l;
	return (new_tab);
}
