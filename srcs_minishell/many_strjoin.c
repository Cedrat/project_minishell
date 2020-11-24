/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   many_strjoin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnoaille <lnoaille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/24 18:21:59 by lnoaille          #+#    #+#             */
/*   Updated: 2020/11/24 18:29:40 by lnoaille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

char	*ft_strjoin_freeone(char const *s1, char const *s2)
{
	size_t	len_s1;
	size_t	len_s2;
	char	*s_join;

	len_s1 = ft_strlen(s1);
	len_s2 = ft_strlen(s2);
	if (!(s_join = malloc(sizeof(char) * (len_s1 + len_s2 + 1))))
		return (0);
	len_s1 = 0;
	while (s1[len_s1])
	{
		s_join[len_s1] = s1[len_s1];
		len_s1++;
	}
	len_s2 = 0;
	while (s2[len_s2])
	{
		s_join[len_s1 + len_s2] = s2[len_s2];
		len_s2++;
	}
	s_join[len_s1 + len_s2] = '\0';
	free((char *)s1);
	return (s_join);
}

char	*ft_strjoin_freetwo(char const *s1, char const *s2)
{
	size_t	len_s1;
	size_t	len_s2;
	char	*s_join;

	len_s1 = ft_strlen(s1);
	len_s2 = ft_strlen(s2);
	if (!(s_join = malloc(sizeof(char) * (len_s1 + len_s2 + 1))))
		return (0);
	len_s1 = 0;
	while (s1[len_s1])
	{
		s_join[len_s1] = s1[len_s1];
		len_s1++;
	}
	len_s2 = 0;
	while (s2[len_s2])
	{
		s_join[len_s1 + len_s2] = s2[len_s2];
		len_s2++;
	}
	s_join[len_s1 + len_s2] = '\0';
	free((char *)s2);
	return (s_join);
}

char	*ft_strjoin_freeall(char const *s1, char const *s2)
{
	size_t	len_s1;
	size_t	len_s2;
	char	*s_join;

	len_s1 = ft_strlen(s1);
	len_s2 = ft_strlen(s2);
	if (!(s_join = malloc(sizeof(char) * (len_s1 + len_s2 + 1))))
		return (0);
	len_s1 = 0;
	while (s1[len_s1])
	{
		s_join[len_s1] = s1[len_s1];
		len_s1++;
	}
	len_s2 = 0;
	while (s2[len_s2])
	{
		s_join[len_s1 + len_s2] = s2[len_s2];
		len_s2++;
	}
	s_join[len_s1 + len_s2] = '\0';
	free((char *)s1);
	free((char *)s2);
	return (s_join);
}
