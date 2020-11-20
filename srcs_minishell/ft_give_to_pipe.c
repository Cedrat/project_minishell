/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_give_to_pipe.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnoaille <lnoaille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/19 16:35:36 by lnoaille          #+#    #+#             */
/*   Updated: 2020/11/20 17:38:02 by lnoaille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

int ft_give_to_pipe(t_shell *shell)
{
  pid_t          pid;
  int pipefd[2];
  int fd;
  int next_fd = 0;
  int ret;
	size_t i = 0;
  char **args_pipes;
args_pipes = ft_divide_to_pipe(shell->args);
while(args_pipes[i] != NULL)
{
	shell->args = ft_parser(args_pipes[i]);
	ft_choose_fd(shell);
	pipe(pipefd);
	pid = fork();
		  if (pid == 0)
		  {
			dup2(next_fd, 0);                 // on recupere ou sont ecris les precedentes reponses
			if ((args_pipes[i + 1] != NULL))
				dup2(pipefd[1], 1);           // Si la commande suivante est non nulle, on transmet au futur arguments
			else if (args_pipes[i+1] == NULL)
				dup2(shell->fd, 1);
			close(pipefd[0]);

			ft_get_command(shell); //sort du fils :(
			exit(0);
		  }
		  else
		  {
			wait(&pid);
			close(pipefd[1]);
			next_fd = pipefd[0]; //on recupere next_fd , les arguments sont sur pipefd[0]
			i++;
		  }
	}
}
