/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_errors.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchampda <dchampda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/25 15:42:19 by dchampda          #+#    #+#             */
/*   Updated: 2020/12/17 16:48:18 by lnoaille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

void	ft_strcat_fd(char *str, char *str1, char *str2, int fd)
{
	char	*res;
	int		len;
	int		i;
	int		j;

	len = ft_strlen(str) + ft_strlen(str1) + ft_strlen(str2);
	if (!(res = malloc(sizeof(char) * len + 1)))
		exit(0);
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
	ft_putstr_fd(res, fd);
	free(res);
}

void	ft_errors(int error, t_shell *shell)
{
	if (error == -1)
	{
		if (shell->args[0])
			ft_strcat_fd("Command not found : ", shell->args[0], "\n", 2);
		else
			ft_strcat_fd("Command not found : ", "", "\n", 2);
	}
	else if (error == -2)
		ft_strcat_fd(shell->args[1], " : No file or folder of this type",
													"\n", 2);
	else if (error == -3)
		ft_putstr_fd("Error : Too many/few quotes", 2);
	else if (error == -4)
		ft_putstr_fd("Error, no fd\n", 2);
	else if (error == -5)
		ft_putstr_fd("Error : Too many/few arguments\n", 2);
	else if (error == -6)
		ft_strcat_fd(shell->args[0], " : No file or folder of this type"
		, "\n", 2);
	else if (error == -7)
		ft_putstr_fd("Error with the child processus\n", 2);
	else if (error == -8)
		ft_strcat_fd("cd : ", "« HOME »", " undefined\n", 2);
	if (error == -5 || error == -2 || error == -3 || error == -8)
		shell->signal = 1;
}
