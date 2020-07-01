/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olaurine <olaurine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/14 04:05:18 by olaurine          #+#    #+#             */
/*   Updated: 2020/07/01 17:06:46 by olaurine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int		get_line(char **p_n, char **line, char **remainder)
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
		if ((*p_n)[1] != '\0' && !(*remainder = ft_strdup(*p_n + 1)))
			*remainder = NULL;
		else if ((*p_n)[1] == '\0')
			*remainder = NULL;
		free(temp);
	}
	else
	{
		*line = ft_strdup(*remainder);
		free(*remainder);
		*remainder = NULL;
		if (!(*line))
			return (-1);
		return (0);
	}
	return (1);
}

int		get_next_line(int fd, char **line)
{
	static char		*remainder = NULL;
	char			*temp;
	char			buf[BUFFER_SIZE + 1];
	int				readed;
	char			*p_n;

	if (fd < 0 || !line || BUFFER_SIZE < 1)
		return (-1);
	p_n = remainder ? ft_strchr(remainder, '\n') : NULL;
	readed = 0;
	while (!p_n && (readed = read(fd, buf, BUFFER_SIZE)) > 0)
	{
		buf[readed] = '\0';
		if (!remainder || (!(remainder = ft_strdup(""))))
			return (-1);
		temp = remainder;
		if (!(remainder = ft_strjoin(remainder, buf)))
			free(temp);
			remainder = NULL;
			return (-1);
		free(temp);
		if ((p_n = ft_strchr(remainder, '\n')))
			break;
	}
	if (readed < 0 && (!remainder || remainder[0] == 0))
		return (-1);
	else if (readed == 0 && (!remainder || remainder[0] == 0))
	{
		if (!(*line = ft_strdup("")))
			return (-1);
		return (0);
	}
	return (get_line(&p_n, line, &remainder));
}
