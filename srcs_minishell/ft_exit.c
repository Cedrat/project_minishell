/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchampda <dchampda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/03 16:45:56 by dchampda          #+#    #+#             */
/*   Updated: 2020/12/16 19:50:59 by lnoaille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

static int	ft_exit_illegal_nb(char *str, t_shell *shell)
{
	write(1, "Bye ! \n", 7);
	ft_strcat_fd("minishell: exit : Illegal number: ", str, "\n", 2);
	ft_free_all(shell);
	free(str);
	exit(2);
}

int			ft_exit(t_shell *shell)
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
			ft_exit_illegal_nb(str, shell);
		if (shell->args[2])
		{
			ft_strcat_fd("Bye ! \n", "minishell: exit : Too many args",
			"\n", 2);
			ft_free_all(shell);
			exit(1);
		}
	}
	write(1, "Bye ! \n", 7);
	ft_free_all(shell);
	exit(nb % 256);
}
