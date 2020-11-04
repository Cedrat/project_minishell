/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnoaille <lnoaille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/01 17:37:03 by lnoaille          #+#    #+#             */
/*   Updated: 2020/11/04 18:16:16 by lnoaille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../header/libft.h"

static	void	*ft_freeforall(char **content, size_t x)
{
	size_t i;

	i = 0;
	while (i < x)
	{
		free(content[i]);
		i++;
	}
	free(content);
	return (NULL);
}

static	size_t	ft_nbr_of_split(char const *s, char c)
{
	size_t	begin;
	size_t	count;
	size_t	nbr;

	begin = 0;
	count = 0;
	nbr = 0;
	while (s[count])
	{
		while (s[count] == c && s[count])
			count++;
		begin = count;
		while (s[count] != c && s[count])
			count++;
		if (begin != count)
			nbr++;
	}
	return (nbr);
}

char			**ft_split(char const *s, char c)
{
	char	**tab;
	size_t	count;
	size_t	i;
	size_t	begin;

	count = 0;
	i = 0;
	begin = 0;
	if (!(tab = malloc(sizeof(char*) * (ft_nbr_of_split(s, c) + 1))))
		return (0);
	while (s[count])
	{
		while (s[count] == c && s[count])
			count++;
		begin = count;
		while (s[count] != c && s[count])
			count++;
		if (begin != count)
			if (!(tab[i++] = ft_substr(s, begin, count - begin)))
				return (ft_freeforall(tab, i));
	}
	tab[i] = NULL;
	return (tab);
}
