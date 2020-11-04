/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnoaille <lnoaille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/29 13:54:33 by lnoaille          #+#    #+#             */
/*   Updated: 2020/11/04 18:16:21 by lnoaille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../header/libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t				count;
	unsigned char		*dst_u;
	const unsigned char *src_u;

	if (dst == NULL && src == NULL)
		return (NULL);
	dst_u = dst;
	src_u = src;
	count = 0;
	while (count < len)
	{
		if (dst < src)
			dst_u[count] = src_u[count];
		else
			dst_u[len - count - 1] = src_u[len - count - 1];
		count++;
	}
	return (dst);
}
