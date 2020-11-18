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

int main (int argc, char **argv, char **argenv)
{
	t_shell	shell;	//Structure generale
	char buff[256];
	char cwd[256];
	size_t i = 0;
	char **args;

	shell.argenv = ft_dup_arg(argenv);
	shell.signal= 0;
	while(1)
	{
		ft_putstr("~");
		ft_putstr(getcwd(cwd, 256));
		ft_putstr("$ ");
		read(1, buff, 256);
		while (buff[i] != '\n' && buff[i])
			i++;
		buff[i] = '\0';
		i = 0;
		args = ft_args(buff);
		while (args[i])
		{
			shell.args = ft_parser(args[i]);
			ft_choose_fd(&shell);
			ft_get_command(&shell);
			if (shell.fd != 1)
				close(shell.fd);
			free(shell.args);
			i++;
		}
		free(args);
	}
}
