/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_semicolon.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnoaille <lnoaille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 18:04:11 by lnoaille          #+#    #+#             */
/*   Updated: 2020/12/16 16:48:18 by lnoaille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

int		count_args(char *str)
{
	size_t	p;
	size_t	i;
	size_t	old_i;

	p = 0;
	i = 0;
	old_i = i;
	while (str[i])
	{
		old_i = i;
		i = ft_semi_colon(&str[i]);
		i = old_i + i;
		if (str[i] != '\0')
			i++;
		p++;
	}
	return (p);
}

char	**ft_args(char *str)
{
	char	**tab_args;
	size_t	p;
	size_t	i;
	size_t	old_i;

	p = 0;
	i = 0;
	old_i = i;
	tab_args = malloc(sizeof(char *) * (1 + count_args(str)));
	while (str[i])
	{
		old_i = i;
		i = ft_semi_colon(&str[i]);
		i = old_i + i;
		ft_strndup(&tab_args[p], str, old_i, i);
		if (str[i] != '\0')
			i++;
		p++;
	}
	tab_args[p] = 0;
	return (tab_args);
}

int		ft_semi_colon(char *str)
{
	char	letter;
	size_t	i;

	i = 0;
	letter = ' ';
	while (str[i])
	{
		if (str[i] == '"' && letter != '"' && letter != '\'')
			letter = '"';
		else if (str[i] == '"' && letter == '"')
			letter = ' ';
		else if (str[i] == '\'' && letter == ' ')
			letter = '\'';
		else if (str[i] == '\'' && letter == '\'')
			letter = ' ';
		else if (letter == ' ' && str[i] == ';')
			break ;
		i++;
	}
	return (i);
}
