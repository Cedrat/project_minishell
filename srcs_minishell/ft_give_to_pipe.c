/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_give_to_pipe.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnoaille <lnoaille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/19 16:35:36 by lnoaille          #+#    #+#             */
/*   Updated: 2020/12/16 17:02:41 by lnoaille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

static	void exec_commands(t_shell *shell)
{
	if (shell->fd != -1)
	{
		ft_get_command(shell);
		ft_free_all(shell);
	}
	else
	{
		ft_free_tab(shell->args);
		ft_free_tab(shell->args_line);
		ft_free_tab(shell->argenv);
	}
}
static void		new_argument(t_shell *shell, char *arg_pipe)
{
	ft_free_tab(shell->args);
	shell->args = ft_parser(arg_pipe, shell);
	ft_choose_fd(shell);
}

static void		cleans(int fdin, int fdout, t_shell *shell)
{
	if (dup2(fdin, 0) == -1)
		exit(0);
	if (dup2(fdout, 1) == -1)
		exit(0);
	free_shell_commands(shell);
	free(shell->echo);
	ft_free_tab(shell->args);
}

static void		son_works(int fd[512][2], t_shell *shell,
													char **args_pipes, size_t i)
{
	int pid;

	if (pipe(fd[i]) == -1)
		exit(0);
	if ((pid = fork()) == 0)
	{
		close(fd[i][0]);
		dup2(fd[i][1], 1);
		close(fd[i][1]);
		if (i > 0)
		{
			dup2(fd[i - 1][0], 0);
			close(fd[i - 1][0]);
		}
		ft_free_tab(args_pipes);
		exec_commands(shell);
		exit(0);
	}
	else
	{
		close(fd[i][1]);
		if (i > 0)
			close(fd[i - 1][0]);
	}
}

void				ft_give_to_pipe(t_shell *shell)
{
	int		fd[512][2];
	size_t	i;
	char	**args_pipes;
	int		tmpin;
	int		tmpout;

	i = 0;
	tmpin = dup(0);
	tmpout = dup(1);
	args_pipes = ft_divide_to_pipe(shell->args);
	while (args_pipes[i + 1] && i < 511)
	{
		new_argument(shell, args_pipes[i]);
		son_works(fd, shell, args_pipes, i);
		i++;
	}
	dup2(fd[i - 1][0], 0);
	close(fd[i - 1][0]);
	new_argument(shell, args_pipes[i]);
	ft_free_tab(args_pipes);
	ft_get_command(shell);
	cleans(tmpin, tmpout, shell);
	wait(NULL);
}
