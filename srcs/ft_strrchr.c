/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnoaille <lnoaille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/27 17:42:38 by lnoaille          #+#    #+#             */
/*   Updated: 2020/11/04 18:15:44 by lnoaille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../header/libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int n;
	int pos;

	n = 0;
	pos = -1;
	while (s[n])
	{
		if (s[n] == c)
			pos = n;
		n++;
	}
	if (s[n] == c)
		pos = n;
	if (pos != -1)
		return ((char *)&s[pos]);
	else
		return (NULL);
}
