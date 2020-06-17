/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olaurine <olaurine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/14 04:05:18 by olaurine          #+#    #+#             */
/*   Updated: 2020/06/17 20:21:43 by olaurine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int		get_line(char **line, char **s)
{
	char		*temp;
	int			len;

	len = 0;
	while ((*s)[len] && (*s)[len] != '\n')
		len++;
	if ((*s)[len] == '\n')
	{
		free(*line);
		*line = ft_substr((*s), 0, len);
		temp = ft_strdup((*s) + len + 1);
		free(*s);
		*s = temp;
		if (*s[0] == '\0')
			free(*s);

	}
	else if ((*s)[len] == '\0')
	{
		free(*line);
		*line = ft_strdup(*s);
		free(*s);
	}
	return (1);
}

int		get_next_line(int fd, char **line)
{
	static char	*s;
	char		*temp;
	char		buf[BUFFER_SIZE + 1];
	int			r;

	if (fd < 0 || !line)
		return (-1);
	while ((!s || !ft_strchr(s, '\n')) && (r = read(fd, buf, BUFFER_SIZE)) > 0)
	{
		buf[r] = '\0';
		if (!s)
			s = ft_strdup(buf);
		else
		{
			temp = ft_strjoin(s, buf);
			free(s);
			s = temp;
		}
		if (ft_strchr(buf, '\n'))
			break ;
	}
	if (r < 0 && (!s || s[0] == '\0'))
		return (-1);
	else if (r == 0 && (!s || s[0] == '\0'))
		return (0);
	return (get_line(line, &s));
}
