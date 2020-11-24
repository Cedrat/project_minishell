/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnoaille <lnoaille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/15 15:00:21 by lnoaille          #+#    #+#             */
/*   Updated: 2020/05/21 19:16:48 by lnoaille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *s)
{
	size_t pos;

	pos = 0;
	while (s[pos])
		pos++;
	return (pos);
}

char	*ft_strjoin_f(char const *s1, char const *s2)
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

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*subcopy;
	size_t	count;

	count = 0;
	if (!(subcopy = malloc(sizeof(char) * (len + 1))))
		return (0);
	if (start > ft_strlen(s))
		len = 0;
	while (count < len)
	{
		subcopy[count] = s[count + start];
		count++;
	}
	subcopy[count] = '\0';
	return (subcopy);
}

int		ft_strchr(const char *s, int c)
{
	int pos;

	pos = 0;
	if (s == NULL)
		return (0);
	while (s[pos] != '\0')
	{
		if (s[pos] == c)
			return (1);
		pos++;
	}
	if (s[pos] == c)
		return (1);
	else
		return (0);
}

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t n;

	n = 0;
	while (src[n] && (n + 1) < (dstsize))
	{
		dst[n] = src[n];
		n++;
	}
	if (dstsize != 0)
		dst[n] = '\0';
	while (src[n])
		n++;
	return (n);
}
