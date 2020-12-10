/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchampda <dchampda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/03 16:44:27 by dchampda          #+#    #+#             */
/*   Updated: 2020/12/03 16:44:28 by dchampda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

int		ft_cd(t_shell *shell)
{
	int i;

	i = 0;
	while (shell->args[i])
		i++;
	if (i == 2)
		ft_purify_args(shell->args);
	if (i == 2 && (shell->signal = chdir(shell->args[1])) == 0)
	{
		shell->newline = 1;
		return (shell->signal);
	}
	else if (i == 1)
	{
		shell->newline = 1;
		shell->signal = chdir(shell->home_path);
		if (shell->signal == -1)
			ft_errors(-8, shell);
		return (shell->signal);
	}
	else if (i > 2)
		return (shell->signal = -5);
	else
		return (shell->signal = -2);
}
