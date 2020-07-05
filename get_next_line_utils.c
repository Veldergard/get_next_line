/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olaurine <olaurine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/14 04:05:24 by olaurine          #+#    #+#             */
/*   Updated: 2020/07/05 22:27:37 by olaurine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static size_t	ft_strlen(const char *s)
{
	size_t len;

	len = 0;
	while (s[len])
		len++;
	return (len);
}

char			*ft_strjoin(char const *s1, char const *s2)
{
	size_t	len1;
	size_t	len2;
	size_t	len_sum;
	size_t	i;
	char	*s;

	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	len_sum = len1 + len2;
	if (len_sum < (len1 | len2))
		return (NULL);
	if (!(s = (char*)malloc((len_sum + 1) * sizeof(char))))
		return (NULL);
	i = -1;
	while (++i < len1)
		s[i] = s1[i];
	i = 0;
	while (i < len2)
		s[len1++] = s2[i++];
	s[len1] = '\0';
	return (s);
}

char			*ft_strdup(const char *s)
{
	size_t		i;
	char		*result;

	i = 0;
	while (s[i])
		i++;
	result = (char*)malloc(sizeof(char) * (i + 1));
	if (!result)
		return (NULL);
	i = 0;
	while (s[i])
	{
		result[i] = s[i];
		i++;
	}
	result[i] = '\0';
	return (result);
}

char			*ft_strchr(const char *s, int c)
{
	size_t	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == (unsigned char)c)
			return ((char*)s + i);
		i++;
	}
	if (s[i] == (unsigned char)c)
		return ((char*)s + i);
	return (NULL);
}
