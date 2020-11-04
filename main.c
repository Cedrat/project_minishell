#include "minishell.h"

void ft_putstr(char *word)
{
	while(*word)
	{
		write(1, word, 1);
		word++;
	}
}

int ft_strlen(const char *word)
{
	size_t i;

	i = 0;
	while (word[i])
		i++;
	return(i);
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
		ft_putstr(args[0]);
		ft_putstr("\n");
	}
}
