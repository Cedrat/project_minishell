#include "../header/minishell.h"

int		ft_cd(char *path)
{
	if (chdir(path) == 0)
		return (1);
	else
		return (-1);
}
