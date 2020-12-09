/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnoaille <lnoaille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/09 15:52:36 by lnoaille          #+#    #+#             */
/*   Updated: 2020/12/09 16:25:46 by lnoaille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

int is_right_syntax(char **line)
{
	size_t sep;
	size_t i;

	i = 0;
	sep = 1;
	while (line[i])
	{
		if (!ft_strcmp(line[i], "|") || !ft_strcmp(line[i], ";"))
			sep++;
		else
			sep = 0;
		if (sep == 2)
		{
			ft_strcat("minishell: syntax error near the unexpected symbol «", line[i], "»\n");
			ft_free_tab(line);
			return (0);
		}
		i++;
	}
	if (!ft_strcmp("|", line[i - 1]))
	{
		ft_putstr("minishell : multi_line not supported\n");
		ft_free_tab(line);
		return(0);
	}
	ft_free_tab(line);
	return (1);
}
