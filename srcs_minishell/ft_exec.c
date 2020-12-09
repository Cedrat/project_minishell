/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchampda <dchampda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 17:39:24 by dchampda          #+#    #+#             */
/*   Updated: 2020/12/09 19:42:15 by lnoaille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

void	ft_no_path(char *arg, char **paths, t_shell *shell)
{
	int		i;
	char	*bin;
	int 	pipefd;

	i = 0;
	g_pid = fork();
	if (g_pid == 0)  //Processus enfant
	{
		dup2(shell->fd,1);
		while (paths[i])
		{
			bin = ft_strjoin(paths[i], arg);
			if ((execve(bin, shell->args, shell->argenv)) == -1)
				;
			else
			{
				// free(arg);
				exit(0);
			}
			free(bin);
			i++;
		}
		free(arg);
		ft_errors(-1, shell);
		ft_free_all(shell);
		ft_free_tab(paths);
		exit(-1);
	}
	else if (g_pid > 0)  //Processus parent
	{
		waitpid(g_pid, &shell->signal, WUNTRACED);

	}
	else
	{
		ft_errors(-7, shell);
		exit(-1);
	}
}


void	ft_path(char *arg, t_shell *shell)
{
	g_pid = fork();

	if (g_pid == 0)  //Processus enfant
	{
		dup2(shell->fd,1);
		if (execve(arg, shell->args, shell->argenv) == -1)
		{
				;
			//ft_errors(-6, shell);
			// exit(-1);
		}
		// free(arg);
		ft_errors(-1, shell);
		ft_free_all(shell);
		// ft_free_tab(paths);
		exit(0);
	}
	else if (g_pid > 0)  //Processus parent
		waitpid(g_pid, &shell->signal, WUNTRACED);
	else
	{
		ft_errors(-7, shell);
		exit(-1);
	}
}

void	ft_path_binary(char *arg, t_shell *shell, char **paths)
{
	g_pid = fork();

	if (g_pid == 0)
	{
		dup2(shell->fd,1);
		execve(arg, shell->args, shell->argenv);
		ft_errors(-1, shell);
		ft_free_all(shell);
		ft_free_tab(paths);
		exit(0);
	}
	else if (g_pid > 0)
		waitpid(g_pid, &shell->signal, WUNTRACED);
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
	ft_purify_args(shell->args + 1);
	if (ft_strcmp("/bin/", arg) == 0 || ft_strcmp("/bin", arg) == 0)
	{
		ft_strcat("bash: ", arg, " is a folder\n");
		ft_free_tab(paths);
		return(0);
	}
	if (paths[0] == NULL && ft_strncmp("/bin", arg, 4) != 0)
	{
		ft_strcat("bash: ", shell->args[0], " : No files or folders of this type\n");
		ft_free_tab(paths); //gerer signal d'erreurs
		return(0);
	}

	// 3. Check si il y a un path dans l'arg (comparer)
	while (found_path == 0 && paths[i])
	{
		if (ft_strncmp(paths[i], arg, ft_strlen(paths[i])) == 0)
		{
			ft_free_tab(paths);
			ft_path(arg, shell);
			found_path = 1;
		}
		i++;
	}
	//4. Si pas de path -> aller tester les chemins de PATH dans argenv
	if (found_path == 0)
	{
		if (arg[0] == '.' && arg[1] && arg[1] == '/'
			|| ft_strncmp("/bin/", arg, 5) == 0)
		{
			ft_path_binary(arg, shell, paths);
		}
		// if (arg[0] != '"')
		// 	temp = ft_str_treatement(arg);
		else if (arg[0] != '/')
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
		ft_free_tab(paths);
	}
	// free(arg);
	// ft_free_tab(paths);     //possible cause de bug
	if (shell->signal == 256)
		shell->signal = 130;	//cat + fichier inexistant
	else if (shell->signal > 0)
		shell->signal = 127;	//binaire inexistant
	return (0);
}
