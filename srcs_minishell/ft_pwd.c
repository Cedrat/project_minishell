/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchampda <dchampda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/03 16:52:35 by dchampda          #+#    #+#             */
/*   Updated: 2020/12/16 16:47:33 by lnoaille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

int		ft_pwd(t_shell *shell)
{
	char	*path;
	size_t	path_size;

	path = 0;
	path_size = 255;
	while (!path)
	{
		if (!(path = malloc(sizeof(char) * path_size + 1)))
			exit(0);
		if (getcwd(path, path_size) == NULL)
		{
			free(path);
			path = NULL;
			if (errno = ERANGE)
				path_size *= 2;
			else
				return (shell->signal = -2);
		}
	}
	ft_putstr_fd(path, shell->fd);
	if (shell->newline == 0)
		ft_putstr_fd("\n", shell->fd);
	free(path);
	return (shell->signal = 0);
}
