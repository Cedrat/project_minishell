/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnoaille <lnoaille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/30 15:55:03 by lnoaille          #+#    #+#             */
/*   Updated: 2020/11/04 18:16:07 by lnoaille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../header/libft.h"

char	*ft_strdup(const char *s)
{
	size_t	len;
	char	*copy;
	size_t	count;

	len = 0;
	count = 0;
	while (s[len])
		len++;
	if (!(copy = malloc(sizeof(char) * (len + 1))))
		return (0);
	while (count <= len)
	{
		copy[count] = s[count];
		count++;
	}
	return (copy);
}
