#include "header/minishell.h"

void ft_putstr(char *word)
{
	while(*word)
	{
		write(1, word, 1);
		word++;
	}
}


int main ()
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
		args = ft_split(buff, ' ');
		if (ft_strcmp(args[0], "exit") == 0 && ft_nopipes(args))
			exit(0);
		ft_putstr(args[0]);
		ft_putstr("\n");
	}
}
