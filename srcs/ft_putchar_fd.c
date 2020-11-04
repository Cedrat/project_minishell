/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnoaille <lnoaille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/05 15:32:00 by lnoaille          #+#    #+#             */
/*   Updated: 2020/11/04 18:16:20 by lnoaille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../header/libft.h"

void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}
