/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_choose_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnoaille <lnoaille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/17 16:51:28 by lnoaille          #+#    #+#             */
/*   Updated: 2020/12/08 18:11:28 by lnoaille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

int ft_choose_fd(t_shell *shell)
{
	size_t i;

	shell->fd = 1;
	i = 0;
	while(shell->args[i] != NULL)
	{
		if (!(ft_strcmp(shell->args[i], ">")))
		{
			if (!(shell->args[i + 1]))
			{
				ft_errors(-4, shell);
				return(0);
			}
			if (!ft_strcmp(shell->args[i + 1], ">") || !ft_strcmp(shell->args[i + 1], ">>") || !ft_strcmp(shell->args[i + 1], "<"))
			{
				ft_strcat("minishell: syntax error near the unexpected symbol «", shell->args[i], "»\n");
				return (0); // gerer signal error
			}
			if (shell->fd != 1)
				close(shell->fd);
			shell->fd = open(shell->args[i + 1], O_WRONLY|O_CREAT|O_TRUNC|O_APPEND|O_NONBLOCK, 0644);
			shell->args = ft_remove_in_tab(shell->args, shell->args[i + 1]);
			shell->args = ft_remove_in_tab(shell->args, shell->args[i]);
		}
		else if (!(ft_strcmp(shell->args[i], ">>")))
		{
			if (!(shell->args[i + 1]))
			{
				ft_errors(-4, shell);
				return(0);
			}
			if (!ft_strcmp(shell->args[i + 1], ">") || !ft_strcmp(shell->args[i + 1], ">>") || !ft_strcmp(shell->args[i + 1], "<"))
			{
				ft_strcat("minishell: syntax error near the unexpected symbol «", shell->args[i], "»\n");
				return (0); // gerer signal error
			}
			if (shell->fd != 1)
				close(shell->fd);
			shell->fd = open(shell->args[i + 1], O_WRONLY|O_CREAT|O_APPEND|O_NONBLOCK, 0644);
			shell->args = ft_remove_in_tab(shell->args, shell->args[i + 1]);
			shell->args = ft_remove_in_tab(shell->args, shell->args[i]);
		}
		else if (!(ft_strcmp(shell->args[i], "<")))
		{
			if (!(shell->args[i + 1]))
			{
				ft_errors(-4, shell);
				return(0);
			}
			if (!ft_strcmp(shell->args[i + 1], ">") || !ft_strcmp(shell->args[i + 1], ">>") || !ft_strcmp(shell->args[i + 1], "<"))
			{
				ft_strcat("minishell: syntax error near the unexpected symbol «", shell->args[i], "»\n");
				return (0) ; // gerer signal error
			}
			shell->args = ft_remove_in_tab(shell->args, shell->args[i]);
			if (ft_str_is_present(shell->args, "<"))
				shell->args = ft_remove_in_tab(shell->args, shell->args[i]);
		}
		else
			i++;
	}
	return (1);
}
