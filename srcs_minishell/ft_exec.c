/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchampda <dchampda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 17:39:24 by dchampda          #+#    #+#             */
/*   Updated: 2020/11/16 17:39:26 by dchampda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

void	ft_no_path(char *arg, char **paths, t_shell *shell)
{
	int		i;
	char	*bin;

	i = 0;
	pid = fork();
	if (pid == 0)  //Processus enfant
	{
		while (paths[i])
		{
			bin = ft_strjoin(paths[i], arg);
			if (execve(bin, shell->args, shell->argenv) == -1)
				free(bin);
			else
				exit(0);
			i++;
		}
		ft_putstr(arg);
		ft_putstr(": No file or folder of this type \n");
		exit(-1);
	}
	else if (pid > 0)  //Processus parent
		waitpid(pid, &status, WUNTRACED);
	else
	{
		ft_putstr("Error with the child processus\n");
		exit(-1);
	}
}


void	ft_path(char *arg, t_shell *shell)
{
	pid = fork();

	if (pid == 0)  //Processus enfant
	{
		if (execve(arg, shell->args, shell->argenv) == -1)
		{
			ft_putstr(arg);
			ft_putstr(": No file or folder of this type \n");
			exit(-1);
		}
		exit(0);
	}
	else if (pid > 0)  //Processus parent
		waitpid(pid, &status, WUNTRACED);
	else
	{
		ft_putstr("Error with the child processus\n");
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
	}
	if (status > 0)
		status = -1;
	return (0);
}
