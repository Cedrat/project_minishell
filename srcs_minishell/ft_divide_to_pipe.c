/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_divide_to_pipe.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnoaille <lnoaille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/20 16:27:35 by lnoaille          #+#    #+#             */
/*   Updated: 2020/12/16 17:11:01 by lnoaille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

size_t			count_pipe(char **split)
{
	size_t p;
	size_t i;

	i = 0;
	p = 0;
	while (split[i])
	{
		if (!(ft_strcmp(split[i], "|")))
			p++;
		i++;
	}
	return (p);
}

static	int		split_line_args(char **split, char **new_tab)
{
	size_t i;
	size_t p;

	p = 0;
	i = 0;
	while (split[i])
	{
		if (ft_strcmp(split[i], "|") != 0)
		{
			if ((new_tab[p] = ft_strjoin_freeone(new_tab[p], split[i])) == NULL)
				exit(0);
			if ((new_tab[p] = ft_strjoin_freeone(new_tab[p], " ")) == NULL)
				exit(0);
		}
		else
		{
			p++;
			if ((new_tab[p] = malloc(1)) == NULL)
				exit(0);
			new_tab[p][0] = '\0';
		}
		i++;
	}
	return (p);
}

char			**ft_divide_to_pipe(char **split)
{
	char	**new_tab;
	size_t	p;

	p = count_pipe(split);
	if ((new_tab = malloc(sizeof(char *) * (p + 2))) == NULL)
		exit(0);
	p = 0;
	if ((new_tab[p] = malloc(1)) == NULL)
		exit(0);
	new_tab[p][0] = '\0';
	p = split_line_args(split, new_tab);
	new_tab[p + 1] = NULL;
	return (new_tab);
}
