/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_command.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchampda <dchampda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/03 16:13:24 by dchampda          #+#    #+#             */
/*   Updated: 2020/12/14 17:17:42 by lnoaille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

int		ft_strcmp_cmds(const char *s1, const char *s2)
{
	size_t	pos1;
	size_t	pos2;

	pos1 = 0;
	pos2 = 0;
	while (s1[pos1] == '\'' || s1[pos1] == '"')
		pos1++;
	while (s1[pos1] && s2[pos2] && s1[pos1] == s2[pos2]
		&& s1[pos1 + 1] != '\'' && s1[pos1 + 1] != '"' && s1[pos1 + 1] != ' ')
	{
		pos1++;
		pos2++;
	}
	return ((unsigned char)s1[pos1] - (unsigned char)s2[pos2]);
}

static int check_build_in(int found, char *command, t_shell *shell)
{
	size_t j;

	j = 0;
	while (j < 7 && found == -1)
	{
		if (ft_strcmp_cmds(command, shell->commands[j]) == 0
			&& ft_nopipes(shell->args))
			found = shell->function[j](shell);
		j++;
	}
}

void	ft_init_commands(t_shell *shell)
{
	shell->echo = malloc(sizeof(t_echo));
	shell->commands[0] = ft_strdup("echo");
	shell->commands[1] = ft_strdup("cd");
	shell->commands[2] = ft_strdup("pwd");
	shell->commands[3] = ft_strdup("export");
	shell->commands[4] = ft_strdup("unset");
	shell->commands[5] = ft_strdup("env");
	shell->commands[6] = ft_strdup("exit");
	shell->newline = 0;
	shell->echo->option_n = 1;
}

void	ft_get_command(t_shell *shell)
{
	int		i;
	int		j;
	int		found;
	char 	*tmp;

	ft_init_commands(shell);
	shell->home_path = ft_get_var(shell->argenv, "HOME=");
	i = 0;
	if (shell->args[i] == NULL)
		return ;
	tmp = ft_str_treatement(shell->args[i]);
	free(shell->args[i]);
	shell->args[i] = tmp;
	found = -1;
	while (shell->args[i] && found == -1)
	{
		found = check_build_in(found ,shell->args[i], shell);
		if (found == -1)
			found = ft_exec(shell, shell->args[i]);
		i++;
	}
	ft_errors(found, shell);
	if (shell->echo->option_n == 0 && shell->newline == 0)
		ft_putstr_fd("\n", shell->fd);
}
