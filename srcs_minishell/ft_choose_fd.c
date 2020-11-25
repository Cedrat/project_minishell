/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_choose_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnoaille <lnoaille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/17 16:51:28 by lnoaille          #+#    #+#             */
/*   Updated: 2020/11/24 16:44:11 by lnoaille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

void ft_choose_fd(t_shell *shell)
{
	size_t i;

	shell->fd = 1;
	i = 0;
	while(shell->args[i] != 0)
	{
		if (!(ft_strcmp(shell->args[i], ">")))
		{
			if (!(shell->args[i + 1]))
				return (ft_errors(-4, shell));
			if (shell->fd != 1)
				close(shell->fd);
			shell->fd = open(shell->args[i + 1], O_WRONLY|O_CREAT|O_TRUNC|O_APPEND, 0644);
			shell->args = ft_remove_in_tab(shell->args, shell->args[i + 1]);
			shell->args = ft_remove_in_tab(shell->args, shell->args[i]);
		}
		else if (!(ft_strcmp(shell->args[i], ">>")))
		{
			if (!(shell->args[i + 1]))
				return (ft_errors(-4, shell));
			if (shell->fd != 1)
				close(shell->fd);
			shell->fd = open(shell->args[i + 1], O_WRONLY|O_CREAT|O_APPEND, 0644);
			shell->args = ft_remove_in_tab(shell->args, shell->args[i + 1]);
			shell->args = ft_remove_in_tab(shell->args, shell->args[i]);
		}
		else if (!(ft_strcmp(shell->args[i], "<")))
		{
			if (!(shell->args[i + 1]))
				return (ft_errors(-4, shell));
			shell->args = ft_remove_in_tab(shell->args, shell->args[i]);
			if (ft_str_is_present(shell->args, "<"))
				shell->args = ft_remove_in_tab(shell->args, shell->args[i]);

		}
		else
			i++;
	}
}
