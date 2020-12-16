/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnoaille <lnoaille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/24 18:48:44 by lnoaille          #+#    #+#             */
/*   Updated: 2020/12/15 16:57:59 by lnoaille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

void	free_shell_commands(t_shell *shell)
{
	free(shell->commands[0]);
	free(shell->commands[1]);
	free(shell->commands[2]);
	free(shell->commands[3]);
	free(shell->commands[4]);
	free(shell->commands[5]);
	free(shell->commands[6]);
	free(shell->home_path);
}

void	ft_free_all(t_shell *shell)
{
	free_shell_commands(shell);
	free(shell->echo);
	ft_free_tab(shell->args);
	ft_free_tab(shell->args_line);
	ft_free_tab(shell->argenv);
}
