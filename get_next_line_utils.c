/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejafer <ejafer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/08 10:24:45 by ejafer            #+#    #+#             */
/*   Updated: 2021/12/08 10:24:45 by ejafer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	char	*d;
	char	*s;

	d = (char *) dest;
	s = (char *) src;
	if (dest == NULL && src == NULL)
		return (NULL);
	while (n-- > 0)
	{
		*d = *s;
		d++;
		s++;
	}
	return (dest);
}

int	ft_strlen(const char *s)
{
	int		len;
	char	*str;

	str = (char *) s;
	len = 0;
	while (*(str++))
		len++;
	return (len);
}

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

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	const size_t	slen = ft_strlen(src);

	if (slen + 1 < size)
		ft_memcpy(dst, src, slen + 1);
	else if (size != 0)
	{
		ft_memcpy(dst, src, size - 1);
		dst[size - 1] = '\0';
	}
	return (slen);
}

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	const size_t	dstlen = ft_strlen(dst);
	const size_t	srclen = ft_strlen(src);
	const size_t	appendlen = dstsize - dstlen - 1;
	char			*offset;

	if (dstsize < dstlen + 1)
		return (dstsize + srclen);
	offset = dst + dstlen;
	if (srclen < appendlen)
	{
		ft_memcpy(offset, src, srclen + 1);
	}
	else if (appendlen > 0)
	{
		ft_memcpy(offset, src, appendlen);
		*(offset + appendlen) = '\0';
	}
	return (dstlen + srclen);
}
