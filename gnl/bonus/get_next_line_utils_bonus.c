/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhernang <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 13:05:47 by mhernang          #+#    #+#             */
/*   Updated: 2023/02/28 13:06:10 by mhernang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../get_next_line_bonus.h"

char	*cat_mem_buf(char *mem, char *buf, int read)
{
	int		i;
	int		j;
	char	*temp;

	i = 0;
	j = 0;
	if (mem)
		temp = malloc(ft_strlen(mem) + read + 1);
	else
		temp = malloc(read + 1);
	if (mem)
		while (mem[i])
		temp[j++] = mem[i++];
	i = 0;
	while (read > 0)
	{
		temp[j++] = buf[i++];
		read--;
	}
	temp[j] = '\0';
	free(mem);
	mem = temp;
	return (mem);
}

char	*ft_strdup(const char *src)
{
	char	*target;
	int		i;

	target = malloc(ft_strlen(src) + 1);
	if (!target)
		return (NULL);
	i = 0;
	while (src[i])
	{
		target[i] = src[i];
		i++;
	}
	target[i] = '\0';
	return (target);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char			*t;
	unsigned int	i;
	unsigned int	len_str;

	i = 0;
	if (!s)
		return (NULL);
	if (start >= ft_strlen(s))
	{
		t = malloc(1);
		if (!t)
			return (NULL);
		t[0] = 0;
		return (t);
	}
	len_str = ft_strlen(&s[start]);
	if (len < len_str)
		len_str = len;
	t = malloc (len_str * sizeof(char) + 1);
	if (!t)
		return (NULL);
	while (s[start] && len-- > 0)
		t[i++] = s[start++];
	t[i] = '\0';
	return ((char *) t);
}

size_t	ft_strlen(const char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		i++;
	}
	return (i);
}

int	line_has_n(char *buf)
{
	ssize_t	j;

	if (!buf)
		return (-1);
	j = 0;
	while (buf[j])
	{
		if (buf[j] == '\n')
			return (j);
		j++;
	}
	return (-1);
}
