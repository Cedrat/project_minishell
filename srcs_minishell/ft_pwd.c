#include "../header/minishell.h"

int		ft_pwd(t_shell *shell)
{
	char 	*path;
	size_t	path_size;

	path = 0;
	path_size = 255;
	while (!path)
	{
		path = malloc(sizeof(char) * path_size + 1);
		if (getcwd(path, path_size) < 0)
		{
			free(path);
			path = NULL;
			if (errno = ERANGE)
				path_size *= 2;
			else
				return (shell->signal = -2);
		}
	}
	ft_putstr_fd(path, shell->fd);
	ft_putstr_fd("\n", shell->fd);
	free(path);
	return (shell->signal = 0);
}
