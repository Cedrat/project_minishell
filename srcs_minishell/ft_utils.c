/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchampda <dchampda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/20 16:54:09 by dchampda          #+#    #+#             */
/*   Updated: 2020/12/17 16:52:26 by lnoaille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

void	ft_putstr(char *word)
{
	while (*word)
	{
		write(1, word, 1);
		word++;
	}
}

void	ft_inc_values(size_t *i, size_t *j)
{
	*i += 1;
	*j += 1;
}

void	ft_init(size_t *i, size_t *j)
{
	*i = 0;
	*j = 0;
}

char	**ft_dup_arg(char **arg)
{
	size_t	i;
	char	**new_tab;

	i = 0;
	while (arg[i])
		i++;
	if (!(new_tab = malloc(sizeof(char *) * (i + 1))))
		return (NULL);
	i = 0;
	while (arg[i])
	{
		new_tab[i] = ft_strdup(arg[i]);
		i++;
	}
	new_tab[i] = NULL;
	return (new_tab);
}

void	ft_free_tab(char **tab)
{
	size_t	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}
