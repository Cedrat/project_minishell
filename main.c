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

int main (int argc, char **argv, char **argenv)
{
	t_shell	shell;	//Structure generale
	char buff[256];
	char cwd[256];
	size_t i = 0;

	shell.argenvs = ft_convert_2dchar_chainedlist(argenv);
	while(1)
	{
		ft_putstr("~");
		ft_putstr(getcwd(cwd, 256));
		ft_putstr("$ ");
		read(1, buff, 256);
		while (buff[i] != '\n')
			i++;
		buff[i] = '\0';
		i = 0;

		shell.args = ft_parser(buff);
		shell.argenv = argenv;
		ft_get_command(&shell);
		free(shell.args);
	}
}
