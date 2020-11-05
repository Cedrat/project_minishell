#include "../header/minishell.h"

int		ft_exit()
{
	write(1, "Bye ! \n", 7);
	exit(0);
}