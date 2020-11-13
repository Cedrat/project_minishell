#include "../header/minishell.h"

int		ft_pwd(t_shell *shell)
{
	char 	*path;
	size_t	path_size;

	path_size = 255;
	while (!path)
	{
		path = malloc(sizeof(char) * path_size + 1);
		if (!getcwd(path, path_size))
		{
			free(path);
			path = NULL;
			if (errno = ERANGE)
				path_size *= 2;
			else
				return (shell->signal = -1);
		}
	}
	ft_putstr(path);
	return (shell->signal = 1);
}