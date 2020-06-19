/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olaurine <olaurine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/14 04:05:18 by olaurine          #+#    #+#             */
/*   Updated: 2020/06/19 20:22:04 by olaurine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int		get_line(char **p_n, char **line, char **remainder)
{
	char		*temp;

	*p_n = *p_n ? *p_n : ft_strchr(*remainder, '\0');
	if (**p_n == '\n')
	{
		**p_n = 0;
		*line = ft_strdup(*remainder);
		temp = *remainder;
		*remainder = ft_strdup(*p_n + 1);
		free(temp);
		if (*remainder[0] == 0)
		{
			free(*remainder);
			*remainder = NULL;
		}
	}
	else if (**p_n == 0)
	{
		*line = *remainder;
		remainder = NULL;
		return (0);
	}
	return (1);
}

int		get_next_line(int fd, char **line)
{
	static char		*remainder;
	char			*temp;
	char			buf[BUFFER_SIZE + 1];
	int				readed;
	char			*p_n;

	if (fd < 0 || !line || BUFFER_SIZE < 1)
		return (-1);
	p_n = remainder ? ft_strchr(remainder, '\n') : NULL;
	while (!p_n && (readed = read(fd, buf, BUFFER_SIZE)))
	{
		buf[readed] = 0;
		if (!remainder)
			remainder = ft_strdup(buf);
		else
		{
			temp = remainder;
			remainder = ft_strjoin(remainder, buf);
			free(temp);
		}
		if ((p_n = ft_strchr(remainder, '\n')))
			break;
	}
	if (readed < 0 && (!remainder || remainder[0] == 0))
		return (-1);
	else if (readed == 0 && (!remainder || remainder[0] == 0))
		return(0);
	return (get_line(&p_n, line, &remainder));
}
