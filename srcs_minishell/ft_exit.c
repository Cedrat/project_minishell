/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchampda <dchampda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/03 16:45:56 by dchampda          #+#    #+#             */
/*   Updated: 2020/12/07 16:05:32 by lnoaille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"


int		ft_exit(t_shell *shell)
{
	char	*str;
	int		nb;

	nb = 0;
	if (shell->args[1])
	{
		str = ft_str_treatement(shell->args[1]);
		if (ft_str_is_number(str))
			nb = ft_atoi(str);
		else
		{
			ft_putstr("minishell: exit : Illegal number: ");
			ft_putstr(str);
			ft_putstr("\n");
			return (0);
		}
	}
	nb = nb % 256;
	write(1, "Bye ! \n", 7);
	ft_free_all(shell);
	exit(nb);
}
