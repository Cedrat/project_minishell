#include "header/minishell.h"

void 	ft_put_prompt()
{
	char 	*cwd;
	size_t	cwd_size;

	cwd = 0;
	cwd_size = 255;
	while (!cwd)
	{
		cwd = malloc(sizeof(char) * cwd_size + 1);
		if (getcwd(cwd, cwd_size) < 0)
		{
			free(cwd);
			cwd = NULL;
			if (errno = ERANGE)
				cwd_size *= 2;
			else
				return ;
		}
	}
	ft_strcat("~", cwd, "$ ");
	free(cwd);
}

void    sig_handler(int signum)
{
	if (g_pid == 0)
	{
		kill(g_pid, SIGTERM);
		ft_putstr("\n");
		return ;
	}
	if (signum == SIGINT) //ctrl-c = interrupt
	{
		ft_putstr("\n");
		ft_put_prompt();
		g_prompt = 0;
		return ;
	}
	else if (signum == SIGQUIT) //ctrl-\ =quit
	{
		write(1, "\b\b  \b\b", 6); // Erase ctrl-backslash
		return ;
	}
	else if (signum == SIGPIPE) //ctrl-\ =quit
	{
		ft_putstr("PIPE FULL");
	}
}

void 	ft_init_main(t_shell *shell, char **argenv)
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
	int i;

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
}

int main (int argc, char **argv, char **argenv)
{
	t_shell	shell;
	char	*buff;
	size_t	i;
	char	**args;


	ft_init_main(&shell, argenv);
	if ((signal(SIGINT, sig_handler) == SIG_ERR)
		|| (signal(SIGQUIT, sig_handler) == SIG_ERR) || (signal(SIGPIPE, sig_handler)))
		ft_putstr("Error catching signal\n");
	while(1)
	{
		if (g_prompt)
			ft_put_prompt();
		ft_get_line(&buff, &shell);
		if (is_right_syntax(ft_parser(buff, &shell)))
		{
			shell.args_line = ft_args(buff);
			free(buff);
			i = 0;
			g_prompt = 1;
			while (shell.args_line[i])
			{
				shell.args = ft_parser(shell.args_line[i], &shell);
				if (ft_str_is_present(shell.args, "|"))
					ft_give_to_pipe(&shell);
				else
				{			//Faire un ft_launch qui regroupe tout ce bloc ?
						if (ft_choose_fd(&shell) == 0)
						{
							ft_free_tab(shell.args);
							break;
						}
						ft_get_command(&shell);
						if (shell.fd != 1)
							close(shell.fd);
						dup2(shell.tmp_in, 0);
						free(shell.echo);
						free_shell_commands(&shell);
					ft_free_tab(shell.args);
				}
				i++;
			}
			ft_free_tab(shell.args_line);
		}
		else
			free(buff);
	}
}
