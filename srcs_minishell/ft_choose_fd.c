/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_choose_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnoaille <lnoaille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/17 16:51:28 by lnoaille          #+#    #+#             */
/*   Updated: 2020/12/16 19:37:05 by lnoaille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

static	int	redirect_right(t_shell *shell, size_t i)
{
	if (!(shell->args[i + 1]))
	{
		ft_errors(-4, shell);
		return (0);
	}
	shell->fd = open(shell->args[i + 1], O_WRONLY | O_CREAT
											| O_TRUNC | O_NONBLOCK, 0644);
	if (shell->fd == -1)
	{
		if (shell->name_error == NULL)
			shell->name_error = ft_strdup(shell->args[i + 1]);
	}
	shell->args = ft_remove_in_tab(shell->args, shell->args[i + 1]);
	shell->args = ft_remove_in_tab(shell->args, shell->args[i]);
	return (1);
}

static	int	redirect_right_right(t_shell *shell, size_t i)
{
	if (!(shell->args[i + 1]))
	{
		ft_errors(-4, shell);
		return (0);
	}
	shell->fd = open(shell->args[i + 1], O_WRONLY | O_CREAT |
											O_APPEND | O_NONBLOCK, 0644);
	if (shell->fd == -1)
	{
		if (shell->name_error == NULL)
			shell->name_error = ft_strdup(shell->args[i + 1]);
	}
	shell->args = ft_remove_in_tab(shell->args, shell->args[i + 1]);
	shell->args = ft_remove_in_tab(shell->args, shell->args[i]);
	return (1);
}

static	int	redirect_left(t_shell *shell, size_t i)
{
	int fd_in;

	shell->tmp_in = dup(0);
	fd_in = open(shell->args[i + 1], O_RDONLY, 0644);
	if (!(shell->args[i + 1]))
	{
		ft_errors(-4, shell);
		return (0);
	}
	if (fd_in == -1)
	{
		if (shell->name_error == NULL)
			shell->name_error = ft_strdup(shell->args[i + 1]);
		shell->fd = -1;
	}
	shell->args = ft_remove_in_tab(shell->args, shell->args[i + 1]);
	shell->args = ft_remove_in_tab(shell->args, shell->args[i]);
	if (ft_str_is_present(shell->args, "<"))
		shell->args = ft_remove_in_tab(shell->args, shell->args[i]);
	dup2(fd_in, 0);
	return (1);
}

int			ft_choose_fd(t_shell *shell)
{
	size_t i;

	shell->name_error = NULL;
	shell->fd = 1;
	shell->tmp_in = dup(0);
	i = 0;
	while (shell->args[i] != NULL)
	{
		if (!(ft_strcmp(shell->args[i], ">")))
			redirect_right(shell, i);
		else if (!(ft_strcmp(shell->args[i], ">>")))
			redirect_right_right(shell, i);
		else if (!(ft_strcmp(shell->args[i], "<")))
			redirect_left(shell, i);
		else
			i++;
	}
	if (shell->fd == -1)
	{
		ft_strcat_fd("minishell: ", shell->name_error,
			": Permission not granted\n", 2);
		free(shell->name_error);
		return (0);
	}
	return (1);
}
//signal error
