#include "header/minishell.h"

void ft_putstr(char *word)
{
	while(*word)
	{
		write(1, word, 1);
		word++;
	}
}


t_list *ft_convert_2dchar_chainedlist(char **str)
{
	size_t i;
	t_list *char_list;
	t_list *new;

	i = 0;
	char_list = ft_lstnew(str[i]);
	i++;
	while (str[i])
	{
		new = ft_lstnew(str[i]);
		ft_lstadd_back(&char_list, new);
		i++;
	}
	return (char_list);
}

char **ft_dup_arg(char **arg)
{
	size_t i = 0;
	char **new_tab;

	while (arg[i])
		i++;
	new_tab = malloc(sizeof(char *) * (i + 1));
	i = 0;

	while (arg[i])
	{
		new_tab[i] = ft_strdup(arg[i]);
		i++;
	}
	new_tab[i] = 0;
	return (new_tab);
}

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

int main (int argc, char **argv, char **argenv)
{
	t_shell	shell;	//Structure generale
	char *buff;
	size_t i = 0;
	char **args;

	shell.argenv = ft_dup_arg(argenv);
	shell.signal= 0;
	pid = 1;
	prompt = 1;

	if ((signal(SIGINT, sig_handler) == SIG_ERR)
   		|| (signal(SIGQUIT, sig_handler) == SIG_ERR))
		ft_putstr("Error catching signal\n");

	while(1)
	{
		if (prompt)
			ft_put_prompt();

		i = get_next_line(0, &buff);
		if (i == -1)
		{
			ft_putstr("\n");
			exit(0);
		}
		else if (i == -2)
			ft_putstr("\n");

		i = 0;
		args = ft_args(buff);
		prompt = 1;
		while (args[i])
		{
			shell.args = ft_parser(args[i]);
			ft_choose_fd(&shell);
			if (ft_charispresent(args[i], '|'))
				ft_give_to_pipe(&shell);
			else
				ft_get_command(&shell);
			if (shell.fd != 1)
				close(shell.fd);
			free(shell.args);
			i++;
		}
		free(args);
	}
}
