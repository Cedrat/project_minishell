/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_give_to_pipe.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnoaille <lnoaille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/19 16:35:36 by lnoaille          #+#    #+#             */
/*   Updated: 2020/11/19 19:27:59 by lnoaille         ###   ########.fr       */
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

while(shell->args[i] != NULL)
{
	pipe(pipefd);
	pid = fork();
		  if (pid == 0)
		  {
			dup2(next_fd, 0);                 // on recupere ou sont ecris les precedentes reponses
			if ((shell->args[i + 1] != NULL))
				dup2(pipefd[1], 1);           // Si la commande suivante est non nulle, on transmet au futur arguments
			else if (shell->args[i+1] == NULL)
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
