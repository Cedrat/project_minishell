/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchampda <dchampda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/16 15:27:03 by dchampda          #+#    #+#             */
/*   Updated: 2020/12/16 17:21:28 by lnoaille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header/minishell.h"

void	ft_put_prompt(void)
{
	char	*cwd;
	size_t	cwd_size;

	cwd = 0;
	cwd_size = 255;
	while (!cwd)
	{
		if (!(cwd = malloc(sizeof(char) * cwd_size + 1)))
			return ;
		if (getcwd(cwd, cwd_size) == NULL)
		{
			free(cwd);
			cwd = NULL;
			if (errno = ERANGE)
				cwd_size *= 2;
			else
				return ;
		}
	}
	ft_strcat("\033[94;1m~", cwd, "$ \033[0m");
	free(cwd);
}

void	sig_hdl(int signum)
{
	if (g_pid == 0)
	{
		kill(g_pid, SIGTERM);
		ft_putstr("\n");
		return ;
	}
	if (signum == SIGINT)
	{
		ft_putstr("\n");
		ft_put_prompt();
		g_prompt = -1;
		return ;
	}
	else if (signum == SIGQUIT)
	{
		write(1, "\b\b  \b\b", 6);
		return ;
	}
	else if (signum == SIGPIPE)
	{
		ft_putstr("PIPE FULL");
	}
}

void	ft_init_main(t_shell *shell, char **argenv)
{
	shell->function[0] = &ft_echo;
	shell->function[1] = &ft_cd;
	shell->function[2] = &ft_pwd;
	shell->function[3] = &ft_export;
	shell->function[4] = &ft_unset;
	shell->function[5] = &ft_env;
	shell->function[6] = &ft_exit;
	g_pid = 1;
	g_prompt = 1;
	shell->argenv = ft_dup_arg(argenv);
	shell->signal = 0;
	shell->nb_error = 0;
}

void	ft_get_line(char **buff, t_shell *shell)
{
	int	i;

	i = get_next_line(0, buff);
	if (i == -1)
	{
		ft_putstr("\n");
		free(*buff);
		ft_free_tab(shell->argenv);
		exit(0);
	}
	else if (i == -2)
		ft_putstr("\n");
	else if (i == -3)
	{
		ft_putstr("Error : Command line is too long\n");
		g_prompt = 0;
		free(*buff);
		buff[0] = ft_strdup("\0");
	}
	if (g_prompt == -1)
		shell->signal = 130;
}

void	ft_launch(t_shell *shell)
{
	size_t	i;

	i = 0;
	while (shell->args_line[i])
	{
		shell->args = ft_parser(shell->args_line[i], shell);
		if (ft_str_is_present(shell->args, "|"))
			ft_give_to_pipe(shell);
		else
		{
			if (ft_choose_fd(shell) == 0)
			{
				ft_free_tab(shell->args);
				break ;
			}
			ft_get_command(shell);
			if (shell->fd != 1)
				close(shell->fd);
			dup2(shell->tmp_in, 0);
			free(shell->echo);
			free_shell_commands(shell);
			ft_free_tab(shell->args);
		}
		i++;
	}
}

int		main(int argc, char **argv, char **argenv)
{
	t_shell	shell;
	char	*buff;

	(void)argc;
	(void)argv;
	ft_init_main(&shell, argenv);
	if ((signal(SIGINT, sig_hdl) == SIG_ERR)
	|| (signal(SIGQUIT, sig_hdl) == SIG_ERR) || (signal(SIGPIPE, sig_hdl)))
		ft_putstr("Error catching signal\n");
	while (1)
	{
		if (g_prompt > 0)
			ft_put_prompt();
		ft_get_line(&buff, &shell);
		if (is_right_syntax(ft_parser(buff, &shell), &shell))
		{
			shell.args_line = ft_args(buff);
			free(buff);
			g_prompt = 1;
			ft_launch(&shell);
			ft_free_tab(shell.args_line);
		}
		else
			free(buff);
	}
}
