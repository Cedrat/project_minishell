/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnoaille <lnoaille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/19 00:25:24 by lnoaille          #+#    #+#             */
/*   Updated: 2020/12/19 00:29:00 by lnoaille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

void clean_shell(t_shell *shell)
{
	dup2(shell->tmp_in, 0);
	free(shell->echo);
	free_shell_commands(shell);
	ft_free_tab(shell->args);
	if (shell->fd != 1)
		close(shell->fd);
}
