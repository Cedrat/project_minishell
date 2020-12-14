/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchampda <dchampda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/20 16:54:09 by dchampda          #+#    #+#             */
/*   Updated: 2020/11/25 00:13:27 by lnoaille         ###   ########.fr       */
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

t_list	*ft_convert_2dchar_chainedlist(char **str)
{
	size_t	i;
	t_list	*char_list;
	t_list	*new;

	i = 0;
	char_list = ft_lstnew(str[i]);
	i++;
	while (str[i])
	{
		new = ft_lstnew(str[i]);
		ft_lstadd_back(&char_list, new);
		i++;
	}
	return (char_list);
}

void	ft_inc_values(size_t *i, size_t *j)
{
	*i += 1;
	*j += 1;
}

char	**ft_dup_arg(char **arg)
{
	size_t	i;
	char	**new_tab;

	i = 0;
	while (arg[i])
		i++;
	new_tab = malloc(sizeof(char *) * (i + 1));
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
