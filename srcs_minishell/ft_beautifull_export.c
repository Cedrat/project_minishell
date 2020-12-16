/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_beautifull_export.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnoaille <lnoaille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/13 18:54:02 by lnoaille          #+#    #+#             */
/*   Updated: 2020/12/16 18:33:19 by lnoaille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

static	void	set_to_zeros(size_t *i, size_t *j)
{
	*i = 0;
	*j = 0;
}

void			ft_beautifull_export(char *str, int is_export, int fd)
{
	char	letter;
	size_t	i;

	i = 0;
	letter = ' ';
	while (str[i])
	{
		if (str[i] == '"' && letter != '"' && letter != '\'')
			letter = '"';
		else if (str[i] == '"' && letter == '"')
			letter = ' ';
		else if (str[i] == '\'' && letter == ' ')
			letter = '\'';
		else if (str[i] == '\'' && letter == '\'')
			letter = ' ';
		else if (str[i] == '"' && letter == '\'')
		{
			if (is_export)
				write(1, "\\", 1);
			write(fd, &str[i], 1);
		}
		else
			write(fd, &str[i], 1);
		i++;
	}
}

char			*ft_str_treatement(char *str)
{
	char	letter;
	char	*newstr;
	size_t	i;
	size_t	p;

	set_to_zeros(&i, &p);
	letter = ' ';
	while (str[i])
	{
		if (str[i] == '"' && letter != '"' && letter != '\'')
			letter = '"';
		else if (str[i] == '"' && letter == '"')
			letter = ' ';
		else if (str[i] == '\'' && letter == ' ')
			letter = '\'';
		else if (str[i] == '\'' && letter == '\'')
			letter = ' ';
		else
			str[p++] = str[i];
		i++;
	}
	str[p] = '\0';
	if ((newstr = ft_strdup(str)) == NULL)
		exit(0);
	return (newstr);
}
