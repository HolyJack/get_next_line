/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_ next_line.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejafer <ejafer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/08 09:27:09 by ejafer            #+#    #+#             */
/*   Updated: 2021/12/08 09:27:09 by ejafer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strdup(const char *s)
{
	const int	slen = ft_strlen(s);
	char		*tmp;

	tmp = (char *) malloc(sizeof(char) * slen + 1);
	if (tmp == NULL)
		return (NULL);
	ft_memcpy(tmp, s, slen + 1);
	return (tmp);
}

char	*ft_strchr(const char *s, int c)
{
	char	*str;
	size_t	ssize;

	str = (char *) s;
	ssize = ft_strlen(s) + 1;
	while (ssize-- > 0)
	{
		if (*str == (char) c)
			return (str);
		str++;
	}
	return (NULL);
}

char	*ft_strjoin(const char *s1, char const *s2)
{
	char	*nstr;
	size_t	s1_len;
	size_t	s2_len;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	nstr = (char *) malloc(sizeof(char) * (s1_len + s2_len + 1));
	if (nstr == NULL)
		return (NULL);
	ft_memset(nstr, '\0', s1_len + s2_len + 1);
	ft_strlcpy(nstr, s1, s1_len + 1);
	ft_strlcat(nstr, s2, s1_len + s2_len + 1);
	return (nstr);
}

char	*ft_getline(char **reminder, int fd)
{
	char	*line;
	int		linelen;
	char	*eolptr;

	eolptr = ft_strchr(reminder[fd], '\n');
	if (!eolptr)
	{
		line = ft_strdup(reminder[fd]);
		reminder[fd] = NULL;
		return (line);
	}
	linelen = eolptr - reminder[fd] + 1;
	line = malloc(sizeof(char) * (linelen + 1));
	if (!line)
		return (NULL);
	line[linelen] = '\0';
	ft_memcpy(line, reminder[fd], linelen);
	reminder[fd] = eolptr + 1;
	return (line);
}

char	*get_next_line(int fd)
{
	char		*tmp;
	char		*buf;
	int			rdlen;
	static char	*reminder[1024];

	if (fd < 0)
		return (NULL);
	buf = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buf)
		return (NULL);
	buf[BUFFER_SIZE] = '\0';
	rdlen = read(fd, buf, BUFFER_SIZE);
	while (rdlen > 0)
	{
		buf[rdlen] = '\0';
		if (!reminder[fd])
			reminder[fd] = ft_strdup(buf);
		else
		{
			tmp = reminder[fd];
			reminder[fd] = ft_strjoin(reminder[fd], buf);
			free(reminder[fd]);
		}
		if (ft_strchr(reminder[fd], '\n'))
			break ;
		rdlen = read(fd, buf, BUFFER_SIZE);
	}
	free(buf);
	if (rdlen < 0)
		return (NULL);
	else if (reminder[fd] && *reminder[fd])
		return (ft_getline(reminder, fd));
	return (NULL);
}
