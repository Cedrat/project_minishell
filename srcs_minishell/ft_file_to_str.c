/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_file_to_str.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnoaille <lnoaille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/24 16:11:32 by lnoaille          #+#    #+#             */
/*   Updated: 2020/11/24 16:20:25 by lnoaille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

char *ft_file_to_str(char *path)
{
	char *str;
	int fd;
	struct stat sb;

	stat(path, &sb);
	str = malloc(sizeof(char) * sb.st_size);
	fd = open(path, O_RDONLY);
	read(fd, str, sb.st_size);
	close(fd);
	return (str);
}
