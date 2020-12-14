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

static void	ft_joinpath(char **paths, char *arg, char *bin, t_shell *shell)
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
	int		i;
	char	*bin;

	i = 0;
	g_pid = fork();
	if (g_pid == 0)
	{
		dup2(shell->fd,1);
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
		dup2(shell->fd,1);
		if (execve(arg, shell->args, shell->argenv) != -1)
			exit (0);
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

void		ft_path_binary(char *arg, t_shell *shell, char **paths)
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

static int	ft_check_specific_cases(char **paths, char *arg, t_shell *shell)
{
	if (ft_strcmp("/bin/", arg) == 0 || ft_strcmp("/bin", arg) == 0)
	{
		ft_strcat("minishell: ", arg, " is a folder\n");
		ft_free_tab(paths);
		return(0);
	}
	if (paths[0] == NULL && ft_strncmp("/bin", arg, 4) != 0)
	{
		ft_strcat("minishell: ", shell->args[0],
		" : No files or folders of this type\n");
		ft_free_tab(paths);
		return(0);
	}
	return (1);
}

static void	ft_manage_no_path(char **paths, char *arg, t_shell *shell)
{
	char	*temp;

	if (arg[0] == '.' && arg[1] && arg[1] == '/'
		|| ft_strncmp("/bin/", arg, 5) == 0)
	{
		ft_path_binary(arg, shell, paths);
	}
	else if (arg[0] != '/')
	{
		temp = ft_str_treatement(arg);
		temp = ft_strjoin_freetwo("/", temp);
		ft_no_path(temp, paths, shell);
		free(temp);
	}
	else
	{
		temp = ft_strdup(arg);
		ft_no_path(temp, paths, shell);
		free(temp);
	}
	ft_free_tab(paths);
}

static int	ft_try_path(char **paths, char *arg, t_shell *shell)
{
	int	i;

	i = 0;
	while (paths[i])
	{
		if (ft_strncmp(paths[i], arg, ft_strlen(paths[i])) == 0)
		{
			ft_free_tab(paths);
			ft_path(arg, shell);
			return (1);
		}
		i++;
	}
	return (0);
}

int			ft_exec(t_shell *shell, char *arg)
{
	char	*path_line;
	char	**paths;
	int 	i;
	int		found_path;

	i = 0;
	found_path = 0;
	if (!arg || arg[0] == '\n')
		return (0);
	path_line = ft_get_var(shell->argenv, "PATH=");
	paths = ft_split(path_line, ':');
	free(path_line);
	ft_purify_args(shell->args + 1);
	if (!ft_check_specific_cases(paths, arg, shell))
		return (0);
	if (! ft_try_path(paths, arg, shell))
		ft_manage_no_path(paths, arg, shell);
	if (shell->signal == 256)
		shell->signal = 130;
	else if (shell->signal > 0)
		shell->signal = 127;
	return (0);
}
