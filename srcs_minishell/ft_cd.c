#include "../header/minishell.h"

int		ft_cd(char **path, char *home)
{
	int i;

	i = 0;
	while (path[i])
		i++;
	if (i == 2 && chdir(path[1]) == 0)
		return (1);
	else if (i == 1)
	{
		chdir(home);
		return (1);
	}
	else if (i > 2)
		return (-2);
	else
		return (-1);
}
