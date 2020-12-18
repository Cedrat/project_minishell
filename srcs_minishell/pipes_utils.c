/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnoaille <lnoaille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/18 03:06:30 by lnoaille          #+#    #+#             */
/*   Updated: 2020/12/18 03:09:53 by lnoaille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

void	new_argument(t_shell *shell, char *arg_pipe)
{
	ft_free_tab(shell->args);
	shell->args = ft_parser(arg_pipe, shell);
	ft_choose_fd(shell);
}
