/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_errors.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchampda <dchampda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/25 15:42:19 by dchampda          #+#    #+#             */
/*   Updated: 2020/11/26 19:22:05 by lnoaille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

void	ft_strcat(char *str, char *str1, char *str2)
{
	char	*res;
	int		len;
	int 	i;
	int		j;

	len = ft_strlen(str) + ft_strlen(str1) + ft_strlen(str2);
	if (!(res = malloc(sizeof(char) * len + 1)))
		return ;
	i = 0;
	j = 0;
	while (str[j])
		res[i++] = str[j++];
	j = 0;
	while (str1[j])
		res[i++] = str1[j++];
	j = 0;
	while (str2[j])
		res[i++] = str2[j++];
	res[i] = '\0';
	ft_putstr(res);
	free(res);
}

void		ft_errors(int error, t_shell *shell)
{
	if (error == -1)
	{
		if (shell->args[0])
			ft_strcat("Command not found : ", shell->args[0], "\n");
		else
			ft_strcat("Command not found : ", "", "\n");
	}
	else if (error == -2)
		ft_strcat(shell->args[1], " : No file or folder of this type", "\n");
	else if (error == -3)
		ft_putstr("Error : Too many/few quotes");
	else if (error == -4)
		ft_putstr("Error, no fd\n");
	else if (error == -5)
		ft_putstr("Error : Too many/few arguments");
	else if (error == -6)
		ft_strcat(shell->args[0], " : No file or folder of this type", "\n");
	else if (error == -7)
		ft_putstr("Error with the child processus\n");
	if (error != 0)
		shell->nb_error += 1;
}
