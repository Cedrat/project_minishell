/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_purify_args.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnoaille <lnoaille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/07 16:32:59 by lnoaille          #+#    #+#             */
/*   Updated: 2020/12/07 16:37:02 by lnoaille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

void	ft_purify_args(char **args)
{
	size_t	i;
	char	*tmp;

	i = 0;
	while (args[i])
	{
		tmp = ft_str_treatement(args[i]);
		free(args[i]);
		args[i] = tmp;
		i++;
	}
}
