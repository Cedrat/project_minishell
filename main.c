#include "header/minishell.h"

void ft_putstr(char *word)
{
	while(*word)
	{
		write(1, word, 1);
		word++;
	}
}


int main (int argc, char **argv, char **argenv)
{
	char buff[256];
	char cwd[256];
	char **args;
	size_t i = 0;
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

		args = ft_parser(buff);
		ft_get_command(args, argenv);
		free(args);
	}
}
