/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchampda <dchampda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/20 16:54:09 by dchampda          #+#    #+#             */
/*   Updated: 2020/11/20 16:54:10 by dchampda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

void ft_putstr(char *word)
{
	while(*word)
	{
		write(1, word, 1);
		word++;
	}
}

t_list *ft_convert_2dchar_chainedlist(char **str)
{
	size_t i;
	t_list *char_list;
	t_list *new;

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

char **ft_dup_arg(char **arg)
{
	size_t i = 0;
	char **new_tab;

	while (arg[i])
		i++;
	new_tab = malloc(sizeof(char *) * (i + 1));
	i = 0;

	while (arg[i])
	{
		new_tab[i] = ft_strdup(arg[i]);
		i++;
	}
	new_tab[i] = 0;
	return (new_tab);
}