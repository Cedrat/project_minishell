/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchampda <dchampda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 17:39:24 by dchampda          #+#    #+#             */
/*   Updated: 2020/11/27 16:01:36 by lnoaille         ###   ########.fr       */
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
			{
				free(bin);
			}
			else
			{
				// free(arg);
				exit(0);
			}
			i++;
		}
		free(arg);
		ft_errors(-1, shell);
		ft_free_all(shell);
		ft_free_tab(paths);
		exit(-1);
	}
	else if (pid > 0)  //Processus parent
	{
		waitpid(pid, &shell->signal, WUNTRACED);
		// free(arg);

	}
	else
	{
		// free(arg);
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
			// ft_free_all(shell);
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
	char 	*temp;

	i = 0;
	found_path = 0;
	if (!arg || arg[0] == '\n')
		return (0);
	//1. Recuperer ligne PATH
	path_line = ft_get_var(shell->argenv, "PATH=");
	//2.Parser PATH
	paths = ft_split(path_line, ':');
	free(path_line);
	// 3. Check si il y a un path dans l'arg (comparer)
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
		// if (arg[0] != '"')
		// 	temp = ft_str_treatement(arg);
		if (arg[0] != '/') // && arg[0] != '"')
		{
			// if (arg[0] != '"')
			// {
				temp = ft_str_treatement(arg);
				temp = ft_strjoin_freetwo("/", temp);
				ft_no_path(temp, paths, shell);
				// free(arg);
				free(temp);
			// }
			// //path_line = arg;
			// // ft_strjoin("/", arg);
			// else
			// {
			// 	temp = ft_strjoin("/", arg);
			// 	ft_no_path(temp, paths, shell);
			// 	free(temp);
			// }
			//free(path_line);  //Error on valgrind with this line
		}
		else
		{
			temp = ft_strdup(arg);
			ft_no_path(temp, paths, shell);
			free(temp);
		}

	}
	// free(arg);
	ft_free_tab(paths);     //possible cause de bug
	if (shell->signal == 256)
		shell->signal = 130;	//cat + fichier inexistant
	else if (shell->signal > 0)
		shell->signal = 127;	//binaire inexistant
	return (0);
}
