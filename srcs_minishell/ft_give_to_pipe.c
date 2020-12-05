/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_give_to_pipe.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnoaille <lnoaille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/19 16:35:36 by lnoaille          #+#    #+#             */
/*   Updated: 2020/12/05 19:12:50 by lnoaille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

int ft_give_to_pipe(t_shell *shell)
{
		int fd[512][2];
		int i = 0;
		char **args_pipes;
		int tmpin;
		int tmpout;

		tmpin = dup(1);
		tmpout = dup(2);
		args_pipes = ft_divide_to_pipe(shell->args);


		while (args_pipes[i + 1])
		{
			ft_free_tab(shell->args);
			shell->args = ft_parser(args_pipes[i], shell);
			ft_choose_fd(shell);
			pipe(fd[i]);
			if (fork() == 0)
			{
				close(fd[i][0]);
				dup2(fd[i][1], 1);
				close(fd[i][1]);

				if (i > 0)
				{
					dup2(fd[i - 1][0], 0);
					close(fd[i - 1][0]);
				}
				ft_get_command(shell);
				ft_free_tab(args_pipes);
				ft_free_all(shell);
				exit(0);
			}
			else
			{
				close(fd[i][1]);
				if (i > 0)
				{
					close(fd[i - 1][0]);
				}
				i++;
			}
		}
		dup2(fd[i - 1][0], 0);
		close(fd[i - 1][0]);
		ft_free_tab(shell->args);
		shell->args = ft_parser(args_pipes[i], shell);
		ft_choose_fd(shell);
		ft_free_tab(args_pipes);
		ft_get_command(shell);
		dup2(tmpin, 0);
		dup2(tmpout, 1);
		wait(NULL);
		free_shell_commands(shell);
		free(shell->echo);
		ft_free_tab(shell->args);
}
