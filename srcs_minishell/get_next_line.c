/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchampda <dchampda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/13 12:18:47 by dchampda          #+#    #+#             */
/*   Updated: 2020/05/13 12:20:41 by dchampda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

char	*read_file(char *buffer, int fd, int *nb_letters)
{
	char			buf[BUFFER_SIZE + 1];
	int				n;
	char			*tmp;

	n = 0;
	while ((n == 0) && (*nb_letters = read(fd, buf, BUFFER_SIZE)))
	{
		buf[*nb_letters] = '\0';
		if (!buffer)
			buffer = gnl_strndup(buf, ft_strlen(buf));
		else
		{
			tmp = buffer;
			buffer = ft_strjoin(buffer, buf);
			free(tmp);
		}
		if (find_n(buffer, '\n'))
			n = 1;
	}
	return (buffer);
}

int		read_buffer(char *buffer, char **line)
{
	int				i;

	i = 0;
	if (buffer)
	{
		while (buffer[i] != '\0' && buffer[i] != '\n')
			i++;
		if (buffer[i] == '\n')
		{
			*line = gnl_strndup(buffer, i);
			return (1);
		}
		else
		{
			*line = gnl_strndup(buffer, ft_strlen(buffer));
			return (0);
		}
	}
	else
	{
		*line = gnl_strndup("", 0);
		return (0);
	}
}

char	*stock_buffer(char *buffer)
{
	int				i;
	char			*tmp;

	i = 0;
	if (buffer)
	{
		while (buffer[i] != '\n' && buffer[i] != '\0')
			i++;
		if (buffer[i] == '\n')
		{
			tmp = buffer;
			buffer = copy_after_n(buffer, i + 1);
			free(tmp);
		}
	}
	return (buffer);
}

int		get_next_line(int fd, char **line)
{
	static char		*buffer;
	int				nb_letters;
	int				ret;

	if (!line || BUFFER_SIZE < 1 || read(fd, buffer, 0) < 0)
		return (-1);
	buffer = read_file(buffer, fd, &nb_letters);
	if (nb_letters < 0)
		return (-1);
	ret = read_buffer(buffer, line);
	if (ret > 0)
		buffer = stock_buffer(buffer);
	else
	{
		free(buffer);
		buffer = NULL;
		return (0);
	}
	return (1);
}
