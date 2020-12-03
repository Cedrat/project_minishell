/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchampda <dchampda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/03 16:44:57 by dchampda          #+#    #+#             */
/*   Updated: 2020/12/03 16:44:58 by dchampda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

int		ft_env(t_shell *shell)
{
	size_t	i;

	i = 0;
	while (shell->argenv[i])
	{
		if (shell->argenv[0] != 0)
		{
			if (ft_charispresent(shell->argenv[i], '='))
			{
				ft_beautifull_export(shell->argenv[i], 0, shell->fd);
				ft_putstr_fd("\n", shell->fd);
			}
		}
		i++;
	}
	return (shell->signal = 0);
}
