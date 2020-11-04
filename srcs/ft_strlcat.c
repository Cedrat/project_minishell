/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnoaille <lnoaille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/28 11:05:10 by lnoaille          #+#    #+#             */
/*   Updated: 2020/11/04 18:15:26 by lnoaille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../header/libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t len_src;
	size_t count;
	size_t start_c;

	start_c = 0;
	len_src = ft_strlen(src);
	count = ft_strlen(dst);
	while (dstsize > (count + 1 + start_c) && src[start_c])
	{
		dst[count + start_c] = src[start_c];
		start_c++;
	}
	if (dstsize > count)
		dst[count + start_c] = '\0';
	if (dstsize > count)
		dstsize = count;
	return (dstsize + len_src);
}
