/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_second_part.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnoaille <lnoaille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/17 16:50:11 by lnoaille          #+#    #+#             */
/*   Updated: 2020/12/17 17:55:32 by lnoaille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

void		ft_joinpath(char **paths, char *arg, char *bin, t_shell *shell)
{
	int i;

	i = 0;
	while (paths[i])
	{
		bin = ft_strjoin(paths[i], arg);
		if ((execve(bin, shell->args, shell->argenv)) != -1)
			exit(0);
		free(bin);
		i++;
	}
}

void		ft_no_path(char *arg, char **paths, t_shell *shell)
{
	char	*bin;

	bin = NULL;
	g_pid = fork();
	if (g_pid == 0)
	{
		dup2(shell->fd, 1);
		ft_joinpath(paths, arg, bin, shell);
		free(arg);
		ft_errors(-1, shell);
		ft_free_all(shell);
		ft_free_tab(paths);
		exit(-1);
	}
	else if (g_pid > 0)
		waitpid(g_pid, &shell->signal, WUNTRACED);
	else
	{
		ft_errors(-7, shell);
		exit(-1);
	}
}

void		ft_path(char *arg, t_shell *shell)
{
	g_pid = fork();
	if (g_pid == 0)
	{
		dup2(shell->fd, 1);
		if (execve(arg, shell->args, shell->argenv) != -1)
			exit(0);
		else
		{
			ft_errors(-1, shell);
			ft_free_all(shell);
			exit(-1);
		}
	}
	else if (g_pid > 0)
		waitpid(g_pid, &shell->signal, WUNTRACED);
	else
	{
		ft_errors(-7, shell);
		exit(-1);
	}
}
