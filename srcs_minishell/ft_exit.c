/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchampda <dchampda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/03 16:45:56 by dchampda          #+#    #+#             */
/*   Updated: 2020/12/08 16:51:33 by lnoaille         ###   ########.fr       */
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
		{
			nb = ft_atoi(str);
			free(str);
		}
		else
		{
			write(1, "Bye ! \n", 7);
			ft_putstr("minishell: exit : Illegal number: ");
			ft_putstr(str);
			ft_putstr("\n");
			ft_free_all(shell);
			free(str);
			exit(2);
		}
		if (shell->args[2])
		{
			write(1, "Bye ! \n", 7);
			ft_putstr("minishell: exit : Too many args");
			ft_putstr("\n");
			ft_free_all(shell);
			exit(1);
		}
	}
	nb = nb % 256;
	write(1, "Bye ! \n", 7);
	ft_free_all(shell);
	exit(nb);
}
