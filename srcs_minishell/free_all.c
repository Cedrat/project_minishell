/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnoaille <lnoaille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/24 18:48:44 by lnoaille          #+#    #+#             */
/*   Updated: 2020/11/24 18:58:12 by lnoaille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

void free_shell_commands(t_shell *shell)
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
