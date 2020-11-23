/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchampda <dchampda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/13 12:20:56 by dchampda          #+#    #+#             */
/*   Updated: 2020/05/13 12:20:58 by dchampda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# define BUFFER_SIZE 1

int		get_next_line(int fd, char **line);
int		find_n(char *buffer, char c);
char	*gnl_strndup(char *str, int len);
char	*copy_after_n(char *str, int len);

#endif
