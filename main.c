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

int main (int argc, char **argv, char **argenv)
{
	t_shell	shell;	//Structure generale
	char *buff;
	size_t i = 0;
	char **args;

	shell.argenv = ft_dup_arg(argenv);
	shell.signal= 0;
	while(1)
	{
		ft_put_prompt();
		get_next_line(0, &buff);
		while (buff[i]) //buff[i] != '\n' plus nécessaire avec gnl ?
		{
			if (buff[i] == EOF) //Ne fonctionne toujours pas :(
			{
				ft_putstr("\n");
				exit(0);  //A remplacer par un kill avec le pid
			}
			else
				i++;
		}
		//buff[i] == '\0'; //Plus nécessaire avec gnl ?
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
