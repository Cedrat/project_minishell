/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnoaille <lnoaille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/28 16:57:58 by lnoaille          #+#    #+#             */
/*   Updated: 2020/11/04 18:16:48 by lnoaille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../header/libft.h"

void	ft_bzero(void *s, size_t n)
{
	size_t	count;
	char	*word;

	word = s;
	count = 0;
	while (count < n)
	{
		word[count] = '\0';
		count++;
	}
}
