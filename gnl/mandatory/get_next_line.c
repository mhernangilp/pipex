/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhernang <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 13:55:23 by mhernang          #+#    #+#             */
/*   Updated: 2023/02/28 10:55:11 by mhernang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../get_next_line.h"

static void	read_buffer(ssize_t *check, char **mem, char **buf, int *fd)
{
	while (*check && *check != -1 && line_has_n(*mem) == -1)
	{
		*check = read(*fd, *buf, BUFFER_SIZE);
		if (*check > 0)
			*mem = cat_mem_buf(*mem, *buf, *check);
	}
}

static char	*check_result(ssize_t *check, char **mem, char **buf)
{
	char	*ret;

	if (*check == -1 || (*mem && *mem[0] == '\0'))
	{
		if (*mem)
		{
			free(*mem);
			*mem = NULL;
		}
		free(*buf);
		return (NULL);
	}
	if (line_has_n(*mem) != -1)
	{
		ret = return_mem(*mem, 1);
		*mem = ret_out_mem(*mem);
	}
	else
	{
		ret = return_mem(*mem, 0);
		*mem = ret_out_mem(*mem);
	}
	free(*buf);
	return (ret);
}

char	*get_next_line(int fd)
{
	static char	*mem = NULL;
	char		*buf;
	char		*ret;
	ssize_t		check;

	if (fd < 0)
		return (NULL);
	buf = malloc(BUFFER_SIZE);
	if (!buf)
		return (NULL);
	if (mem && line_has_n(mem) != -1)
	{
		ret = return_mem(mem, 1);
		mem = ret_out_mem(mem);
		free(buf);
		return (ret);
	}
	check = 1;
	read_buffer(&check, &mem, &buf, &fd);
	ret = check_result(&check, &mem, &buf);
	return (ret);
}

char	*ret_out_mem(char *mem)
{
	char	*temp;

	if (!mem)
		return (NULL);
	if (line_has_n(mem) != -1)
		temp = ft_strdup(&mem[line_has_n(mem) + 1]);
	else
		temp = ft_strdup(&mem[ft_strlen(mem)]);
	free(mem);
	mem = temp;
	return (mem);
}

char	*return_mem(char *mem, int mode)
{
	int		len;
	char	*ret;

	if (!mem)
		return (NULL);
	if (!mode)
		len = ft_strlen(mem);
	else
		len = line_has_n(mem) + 1;
	ret = ft_substr(mem, 0, len);
	return (ret);
}
