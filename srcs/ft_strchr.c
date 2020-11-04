/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnoaille <lnoaille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/27 17:45:01 by lnoaille          #+#    #+#             */
/*   Updated: 2020/11/04 18:16:14 by lnoaille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../header/libft.h"

char	*ft_strchr(const char *s, int c)
{
	int pos;

	pos = 0;
	while (s[pos])
	{
		if (s[pos] == c)
			return ((char *)&s[pos]);
		pos++;
	}
	if (s[pos] == c)
		return ((char *)&s[pos]);
	else
		return (NULL);
}
