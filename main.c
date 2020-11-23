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
	ft_putstr("~");
	ft_putstr(cwd);
	ft_putstr("$ ");
}

void    sig_handler(int signum)
{
	if (signum == SIGINT) //ctrl-c = interrupt
	{
		if (pid == 0)
		{
			kill(pid, SIGTERM);
			ft_putstr("\n");
			return ;
		}
		else
		{
			ft_putstr("\n");
			ft_put_prompt();
			prompt = 0;
			return ;
		}
	}
	else if (signum == SIGQUIT) //ctrl-\ =quit
	{
		if (pid == 0)
		{
			kill(pid, SIGTERM);
			ft_putstr("\n");
			return ;
		}
		else
		{
			write(1, "\b\b", 2); // Erase ctrl-backslash
			write(1, "  ", 2);
			write(1, "\b\b", 2);
			return ;
		}
	}
}

void 	ft_init_main(t_shell *shell, char **argenv)
{
	pid = 1;
	prompt = 1;
	shell->argenv = ft_dup_arg(argenv);
	shell->signal = 0;
}

void	ft_get_line(char **buff)
{
	int i;

	i = get_next_line(0, buff);
	if (i == -1)
	{
		ft_putstr("\n");
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
		|| (signal(SIGQUIT, sig_handler) == SIG_ERR))
		ft_putstr("Error catching signal\n");
	while(1)
	{
		if (prompt)
			ft_put_prompt();
		ft_get_line(&buff);
		args = ft_args(buff);
		i = 0;
		prompt = 1;
		while (args[i])
		{
			shell.args = ft_parser(args[i]);
			if (ft_charispresent(args[i], '|'))
				ft_give_to_pipe(&shell);
			else
			{
				ft_choose_fd(&shell);
				ft_get_command(&shell);
				if (shell.fd != 1)
					close(shell.fd);
				free(shell.args);
			}
			i++;
		}
		free(args);
	}
}
