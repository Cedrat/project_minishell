/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_args_pipe.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnoaille <lnoaille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/19 18:52:00 by lnoaille          #+#    #+#             */
/*   Updated: 2020/11/19 19:18:47 by lnoaille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

char ***ft_args_pipe(char **args)
{
	char ***args_pipes;
	size_t i = 0;
	size_t p = 0;
	size_t d = 0;

	while(args[i])
	{
		if (!(ft_strcmp(args[i], "|")))
			p++;
		i++;
	}
	args_pipes = malloc(sizeof(char *) * p + 2);

	p = 0;
	i = 0;
	while(args[i])
	{

		if (!(ft_strcmp(args[i], "|")))
		{
			i++;
			p++;
			d = 0;
		}
		else
		{
			args_pipes[p][d] = args[i];
			d++;
		}
		i++;
	}
	puts(args_pipes[0][1]);
	args_pipes[p] = NULL;
}
