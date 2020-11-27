/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_give_to_pipe.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnoaille <lnoaille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/19 16:35:36 by lnoaille          #+#    #+#             */
/*   Updated: 2020/11/27 18:57:03 by lnoaille         ###   ########.fr       */
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
	  int result;
	args_pipes = ft_divide_to_pipe(shell->args);
	ft_free_tab(shell->args);
	while(args_pipes[i] != NULL)
	{
		shell->args = ft_parser(args_pipes[i], shell);
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
				ft_free_all(shell);
				ft_free_tab(args_pipes);
				exit(0);
			  }
			  else
			  {
				  // wait (&pid);
				waitpid(-1 , &pid, 0);
				// printf("||%d ||", WIFEXITED(pid));
				// {
				// 	ft_putstr("warning error not definitive : binary file ?\n");
				// 	break;
				// }
				// waitpid(-1 , &pid, 0);
				close(pipefd[1]);

				next_fd = pipefd[0];
				i++;
			  }
			  ft_free_tab(shell->args);
		}
		ft_free_tab(args_pipes);
}
