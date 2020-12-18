/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnoaille <lnoaille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/06 16:48:44 by lnoaille          #+#    #+#             */
/*   Updated: 2020/12/18 22:32:57 by lnoaille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

int			iterate_word(char *str, size_t *i, size_t p)
{
	char sep;

	sep = str[*i];
	while ((str[*i] == '"' || str[*i] == '\'') && str[*i])
	{
		if (str[*i] == sep)
			p++;
		(*i)++;
	}
	if (p > 1 && p % 2 == 0)
		return (*i);
	while ((str[*i] != '"' && str[*i] != '\'' && str[*i]))
	{
		(*i)++;
	}
	while ((str[*i] == '"' || str[*i] == '\'') && str[*i] && p % 2 != 0)
	{
		if (str[*i] == sep)
			p++;
		(*i)++;
	}
	if (((str[*i] != ' ' && not_a_sep(str[*i])) || (p % 2 != 0)) && str[*i])
		iterate_word(str, i, p);
	return (*i);
}

size_t		count_tokens(char *str)
{
	size_t i;
	size_t j;
	size_t p;
	size_t d;

	i = 0;
	p = 0;
	while (str[i])
	{
		j = ft_is_space(str, &i);
		if (str[i] == '\'' || str[i] == '"')
			d = iterate_word(str, &i, 0);
		else
			d = ft_is_not_space(str, &i);
		if (str[i] == '>' && str[i + 1] == '>')
			ft_inc_values(&i, &p);
		else if (!not_a_sep(str[i]) || j != d)
			p++;
		if (!not_a_sep(str[i]))
			p++;
		if (str[i])
			i++;
	}
	return (p);
}

static void	ft_parser_2(char *str, char **tab, size_t *i, size_t *p)
{
	if (str[*i] == '>' && str[*i + 1] == '>')
	{
		ft_strndup(&tab[*p], str, *i, *i + 2);
		*i += 1;
		*p += 1;
	}
	else if (str[*i] != ' ' && !not_a_sep(str[*i]))
	{
		ft_strndup(&tab[*p], str, *i, *i + 1);
		*p += 1;
	}
	if (str[*i])
		*i += 1;
}

char		**ft_parser(char *str, t_shell *shell)
{
	char	**tab;
	size_t	i;
	size_t	j;
	size_t	p;
	size_t	d;

	if (!(tab = malloc(sizeof(char *) * (count_tokens(str) + 2))))
		return (NULL);
	ft_init(&i, &p);
	while (str[i])
	{
		j = ft_is_space(str, &i);
		if (str[i] == '\'' || str[i] == '"')
			d = iterate_word(str, &i, 0);
		d = ft_is_not_space(str, &i);
		if (j != d)
		{
			ft_strndup(&tab[p], str, j, i);
			p++;
		}
		ft_parser_2(str, tab, &i, &p);
	}
	tab[p] = NULL;
	tab = ft_dollar(tab, shell);
	return (tab);
}
