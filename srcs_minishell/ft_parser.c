/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnoaille <lnoaille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/06 16:48:44 by lnoaille          #+#    #+#             */
/*   Updated: 2020/11/09 17:53:40 by lnoaille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"


void ft_strndup(char **dest, char *src, size_t start, size_t end)
{
	char *str;
	size_t i;
	i = 0;


	str = malloc(sizeof(char) * (end - start + 1));
	while (start < end && src[start])
	{
		str[i] = src[start];
		start++;
		i++;
	}
	str[i] = '\0';
	*dest = str;
}

int not_a_sep(char letter)
{
	if (letter == ';' || letter == '>' || letter == '<' || letter == '|')
		return (0);
	return (1);
}


void iterate_word(char *str, size_t *i, size_t p)
{
	char sep = str[*i];
	while((str[*i] == '"' || str[*i] == '\'') && str[*i])
	{
		if (str[*i] == sep)
			p++;
		(*i)++;
	}
	while((str[*i] != '"' && str[*i] != '\'' && str[*i]))
	{
		(*i)++;
	}
	while((str[*i] == '"' || str[*i] == '\'') && str[*i])
	{
		if (str[*i] == sep)
			p++;
		(*i)++;
	}
	if (((str[*i] != ' ' && not_a_sep(str[*i])) || (p%2 != 0)) && str[*i])
		iterate_word(str, i, p);
}

size_t count_tokens(char *str)
{
	char **tab;
	size_t i = 0;
	size_t j = 0;
	size_t p = 0;
	size_t d = 0;

	while (str[i])
	{
		while(str[i] == ' ')
			i++;
		j = i;
		if (str[i] == '\'' || str[i] == '"')
		{
			iterate_word(str, &i, 0);
			d = i;
		}
		while (not_a_sep(str[i]) && str[i] && str[i] != ' ')
		{
			i++;
		}
		d = i;
		if (j != d)
		{
			p++;
		}
		if (str[i] == '>' && str[i+1] == '>')
		{
			i += 1;
			p++;
		}
		else if (!not_a_sep(str[i]))
		{
					p++;
		}
		if (str[i])
			i++;
	}
	return (p);
}

char **ft_parser(char *str)
{
	char **tab;
	size_t i = 0;
	size_t j = 0;
	size_t p = 0;
	size_t d = 0;

	tab = malloc(sizeof(char *) * (count_tokens(str) + 1));
	while (str[i])
	{
		while(str[i] == ' ')
			i++;
		j = i;
		if (str[i] == '\'' || str[i] == '"')
		{
			iterate_word(str, &i, 0);
			d = i;
		}
		while (not_a_sep(str[i]) && str[i] && str[i] != ' ')
		{
			i++;
		}
		d = i;
		if (j != d)
		{
			ft_strndup(&tab[p], str, j , i );
			p++;
		}
		if (str[i] == '>' && str[i+1] == '>')
		{
			ft_strndup(&tab[p], str, i , i+2);
			i += 1;
			p++;
		}
		else if (!not_a_sep(str[i]))
		{
			ft_strndup(&tab[p], str, i , i+1);
					p++;
		}
		if (str[i])
			i++;
	}
	tab[p] = NULL;
	return (tab);
}

void ft_free_tab_made_by_parser(char **tab)
{
	size_t i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

int main()
{
	char **tab;
	size_t i = 0;
	tab = ft_parser("'test' 'test'");
	while (tab[i])
	{
		printf("%s_\n", tab[i]);
		i++;
	}
	ft_free_tab_made_by_parser(tab);
}
