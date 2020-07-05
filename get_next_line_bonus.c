/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olaurine <olaurine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/02 20:42:29 by olaurine          #+#    #+#             */
/*   Updated: 2020/07/05 22:27:33 by olaurine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

int		separate_line_with_endline(char **line, char **remainder)
{
	*line = ft_strdup(*remainder);
	free(*remainder);
	*remainder = NULL;
	if (!(*line))
		return (-1);
	return (0);
}

int		separate_line(char **p_n, char **line, char **remainder)
{
	char		*temp;

	*p_n = *p_n ? *p_n : ft_strchr(*remainder, '\0');
	if (**p_n == '\n')
	{
		**p_n = '\0';
		if (!(*line = ft_strdup(*remainder)))
		{
			free(*remainder);
			*remainder = NULL;
			return (-1);
		}
		temp = *remainder;
		if (((*p_n)[1] != '\0' && !(*remainder = ft_strdup(*p_n + 1)))
			|| (*p_n)[1] == '\0')
			*remainder = NULL;
		free(temp);
		return (1);
	}
	return (separate_line_with_endline(line, remainder));
}

int		check_read(char **p_n, char **line, char **remainder, int readed)
{
	if (readed < 0 && (!(*remainder) || (*remainder)[0] == 0))
		return (-1);
	else if (readed == 0 && (!(*remainder) || (*remainder)[0] == 0))
	{
		if (!(*line = ft_strdup("")))
			return (-1);
		return (0);
	}
	return (separate_line(p_n, line, remainder));
}

int		get_next_line(int fd, char **line)
{
	static char		*remainder[512];
	char			*temp;
	char			buf[BUFFER_SIZE + 1];
	int				readed;
	char			*p_n;

	if (fd < 0 || !line || BUFFER_SIZE < 1)
		return (-1);
	p_n = remainder[fd] ? ft_strchr(remainder[fd], '\n') : NULL;
	readed = 0;
	while (!p_n && (readed = read(fd, buf, BUFFER_SIZE)) > 0)
	{
		buf[readed] = '\0';
		if (!remainder[fd] && (!(remainder[fd] = ft_strdup(""))))
			return (-1);
		temp = remainder[fd];
		remainder[fd] = ft_strjoin(remainder[fd], buf)
		free(temp);
		if (!remainder && !(remainder[fd] = NULL))
			return (-1);
		free(temp);
		if ((p_n = ft_strchr(remainder[fd], '\n')))
			break;
	}
	return (check_read(&p_n, line, &(remainder[fd]), readed));
}
