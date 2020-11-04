/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnoaille <lnoaille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/29 14:34:17 by lnoaille          #+#    #+#             */
/*   Updated: 2020/11/04 18:16:26 by lnoaille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../header/libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	size_t						count;
	unsigned	char			*dst_temp;
	const	unsigned	char	*src_temp;

	count = 0;
	dst_temp = dst;
	src_temp = src;
	while (count < n)
	{
		dst_temp[count] = src_temp[count];
		if (dst_temp[count] == (unsigned char)c)
			return (dst + count + 1);
		count++;
		src++;
	}
	return (NULL);
}
