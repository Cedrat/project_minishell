/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnoaille <lnoaille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/06 16:48:44 by lnoaille          #+#    #+#             */
/*   Updated: 2020/11/06 18:41:06 by lnoaille         ###   ########.fr       */
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
size_t count_tokens(char *str)
{
	char **tab;
	size_t i = 0;
	size_t j = 0;
	size_t p = 0;

	while (str[i])
	{
		while(str[i] == ' ' && str[i])
			i++;

		j = i;
		if (str[i] == '\'')
		{
			i++;
			while (str[i] != '\'' && str[i])
				i++;
			i++;
		}
		else if (str[i] == '"')
		{
			i++;
			while (str[i] != '"' && str[i])
				i++;
			i++;
		}
		else
		{
			i++;
			while(str[i] != ' ' && str[i])
				i++;
		}
		p++;
	}
	return(p);
}

char **ft_parser(char *str)
{
	char **tab;
	size_t i = 0;
	size_t j = 0;
	size_t p = 0;

	tab = malloc(sizeof(char *) * (count_tokens(str) + 1));
	while (str[i])
	{
		while(str[i] == ' ' && str[i])
			i++;

		j = i;
		if (str[i] == '\'')
		{
					i++;
			while (str[i] != '\'' && str[i])
				i++;
			i++;
		}
		else if (str[i] == '"')
		{
					i++;
			while (str[i] != '"' && str[i])
				i++;
			i++;
		}
		else
		{
					i++;
			while(str[i] != ' ' && str[i])
				i++;
		}
		ft_strndup(&tab[p], str, j ,i);
		p++;
	}
	tab[p] = 0;
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

// int main()
// {
// 	char **tab;
// 	size_t i = 0;
// 	tab = ft_parser("coucou les amis \"salut les\"");
// 	while (tab[i])
// 	{
// 		printf("%s_\n", tab[i]);
// 		i++;
// 	}
// 	ft_free_tab_made_by_parser(tab);
// }
