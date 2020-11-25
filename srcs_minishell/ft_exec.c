/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchampda <dchampda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 17:39:24 by dchampda          #+#    #+#             */
/*   Updated: 2020/11/24 18:40:31 by lnoaille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

void	ft_no_path(char *arg, char **paths, t_shell *shell)
{
	int		i;
	char	*bin;
	int 	pipefd;


	i = 0;

	pid = fork();

	if (pid == 0)  //Processus enfant
	{
		dup2(shell->fd,1);
		while (paths[i])
		{
			bin = ft_strjoin(paths[i], arg);
			if (execve(bin, shell->args, shell->argenv) == -1)
				free(bin);
			else
				exit(0);
			i++;
		}
		ft_errors(-1, shell);
		exit(-1);
	}
	else if (pid > 0)  //Processus parent
		waitpid(pid, &shell->signal, WUNTRACED);
	else
	{
		ft_errors(-7, shell);
		exit(-1);
	}
}


void	ft_path(char *arg, t_shell *shell)
{
	pid = fork();

	if (pid == 0)  //Processus enfant
	{
		dup2(shell->fd,1);
		if (execve(arg, shell->args, shell->argenv) == -1)
		{
			ft_errors(-6, shell);
			exit(-1);
		}
		exit(0);
	}
	else if (pid > 0)  //Processus parent
		waitpid(pid, &shell->signal, WUNTRACED);
	else
	{
		ft_errors(-7, shell);
		exit(-1);
	}
}


int	ft_exec(t_shell *shell, char *arg)
{
	char	*path_line;
	char	**paths;
	int 	i;
	int		found_path;

	i = 0;
	found_path = 0;
	if (!arg || arg[0] == '\n')
		return (0);
	//1. Recuperer ligne PATH
	path_line = ft_get_var(shell->argenv, "PATH=");
	//2.Parser PATH
	paths = ft_split(path_line, ':');
	free(path_line);
	//3. Check si il y a un path dans l'arg (comparer)
	while (paths[i] && found_path == 0)
	{
		if (ft_strncmp(paths[i], arg, ft_strlen(paths[i])) == 0)
		{
			ft_path(arg, shell);
			found_path = 1;
		}
		i++;
	}
	//4. Si pas de path -> aller tester les chemins de PATH dans argenv
	if (found_path == 0)
	{
		if (arg[0] != '/')
		{
			//path_line = arg;
			arg = ft_strjoin("/", arg);
			//free(path_line);  //Error on valgrind with this line
		}
		ft_no_path(arg, paths, shell);
		//free(arg); //Double free si on garde ft_free_tab
	}
	ft_free_tab(paths);     //possible cause de bug
	if (shell->signal > 0)
		shell->signal = -1;
	return (0);
}
