/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnoaille <lnoaille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/09 15:52:36 by lnoaille          #+#    #+#             */
/*   Updated: 2020/12/16 16:46:47 by lnoaille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

int			check_nb_sep(t_shell *shell, int sep, size_t i, char **line)
{
	if (sep == 2)
	{
		ft_strcat("minishell: syntax error near the unexpected symbol «",
												line[i], "»\n");
		ft_free_tab(line);
		shell->signal = 2;
		return (0);
	}
	return (1);
}

static	int	syntax_multi_line(t_shell *shell, size_t i, char **line)
{
	if (i > 1 && !ft_strcmp("|", line[i - 1]))
	{
		ft_putstr("minishell : multi_line not supported\n");
		ft_free_tab(line);
		shell->signal = 22;
		return (0);
	}
	return (1);
}

static	int	two_symbols(t_shell *shell, char **line, size_t i)
{
	if ((!ft_strcmp(line[i], ">") || !ft_strcmp(line[i], ">>") ||
	!ft_strcmp(line[i], "<")) && line[i + 1] &&
		(!ft_strcmp(line[i + 1], "<") || !ft_strcmp(line[i + 1], ">") ||
		!ft_strcmp(line[i + 1], ">>") || !ft_strcmp(line[i + 1], "|")))
	{
		ft_strcat("minishell: syntax error near the unexpected symbol « ",
			line[i + 1], " »\n");
		ft_free_tab(line);
		shell->signal = 2;
		return (0);
	}
	else if ((!ft_strcmp(line[i], ">") || !ft_strcmp(line[i], ">>")
			|| !ft_strcmp(line[i], "<")) && line[i + 1] == NULL)
	{
		ft_strcat("minishell: syntax error near the unexpected symbol «",
								" newline ", "»\n");
		ft_free_tab(line);
		shell->signal = 2;
		return (0);
	}
	return (1);
}

int			is_right_syntax(char **line, t_shell *shell)
{
	size_t sep;
	size_t i;

	i = 0;
	sep = 1;
	while (line[i])
	{
		if (!ft_strcmp(line[i], "|") || !ft_strcmp(line[i], ";"))
			sep++;
		else
			sep = 0;
		if (check_nb_sep(shell, sep, i, line) == 0)
			return (0);
		if (two_symbols(shell, line, i) == 0)
			return (0);
		i++;
	}
	if (syntax_multi_line(shell, i, line) == 0)
		return (0);
	ft_free_tab(line);
	return (1);
}
