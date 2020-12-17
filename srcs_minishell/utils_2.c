/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnoaille <lnoaille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/17 17:42:14 by lnoaille          #+#    #+#             */
/*   Updated: 2020/12/17 19:17:50 by lnoaille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

void		ft_strndup(char **dest, char *src, size_t start, size_t end)
{
	char	*str;
	size_t	i;

	i = 0;
	if (!(str = malloc(sizeof(char) * (end - start + 1))))
		exit(0);
	while (start < end && src[start])
	{
		str[i] = src[start];
		start++;
		i++;
	}
	str[i] = '\0';
	*dest = str;
}

int			not_a_sep(char letter)
{
	if (letter == ';' || letter == '>' || letter == '<' || letter == '|')
		return (0);
	return (1);
}

int			ft_is_not_space(char *str, size_t *i)
{
	while (not_a_sep(str[*i]) && str[*i] && str[*i] != ' ')
	{
		if (str[*i] == '"')
			iterate_word(str, i, 0);
		if (str[*i])
			*i += 1;
	}
	return (*i);
}

int			ft_is_space(char *str, size_t *i)
{
	while (str[*i] == ' ')
		*i += 1;
	return (*i);
}

void		ft_get_line(char **buff, t_shell *shell)
{
	int	i;

	i = get_next_line(0, buff);
	if (i == -1)
	{
		ft_putstr("\n");
		free(*buff);
		ft_free_tab(shell->argenv);
		exit(0);
	}
	else if (i == -2)
		ft_putstr("\n");
	else if (i == -3)
	{
		ft_putstr("Error : Command line is too long\n");
		g_prompt = 0;
		free(*buff);
		buff[0] = ft_strdup("\0");
	}
	if (g_prompt == -1)
		shell->signal = 130;
}
