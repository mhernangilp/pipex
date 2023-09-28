/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhernang <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 21:20:26 by mhernang          #+#    #+#             */
/*   Updated: 2023/09/17 16:59:36 by mhernang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

int	ft_strncmp(char *s1, char *s2, unsigned int n)
{
	unsigned int	i;

	i = 0;
	while (s1[i] != '\0' && s2[i] != '\0' && i < n)
	{
		if (s1[i] != s2[i])
			return (s1[i] - s2[i]);
		++i;
	}
	if (i != n)
		return (s1[i] - s2[i]);
	return (0);
}

static int	ft_delcount(char const *s, char c)
{
	int	i;
	int	count;

	if (s[0] == 0)
		return (0);
	i = 0;
	count = 0;
	if (s[i] == c)
		count--;
	while (s[i])
	{
		if (s[i] == c)
		{
			while (s[i + 1] == c)
				i++;
			if (s[i + 1])
				count++;
		}
		i++;
	}
	count++;
	return (count);
}

static void	ft_loop(char const *s, char *c, int *csize, char **p)
{
	int	i;
	int	j;
	int	count;

	i = 0;
	j = 0;
	while (j < *csize)
	{
		count = 0;
		while (s[i] == *c)
			i++;
		while (s[i] != *c && s[i])
		{
			p[j][count] = s[i];
			i++;
			count++;
		}
		p[j][count] = '\0';
		j++;
	}
}

static void	ft_fillco(char const *s, char c, int csize, char **p)
{
	int	i;
	int	count;
	int	j;

	i = 0;
	j = 0;
	while (j < csize)
	{
		count = 0;
		while (s[i] == c)
			i++;
		while (s[i] != c && s[i])
		{
			count++;
			i++;
		}
		p[j] = malloc(count * sizeof(char) + 1);
		j++;
	}
	ft_loop(s, &c, &csize, p);
}

char	**ft_split(char const *s, char c)
{
	int		cosize;
	char	**p;

	if (!s)
		return (NULL);
	cosize = ft_delcount(s, c);
	p = malloc((cosize + 1) * sizeof(char *));
	if (!p)
		return (NULL);
	p[cosize] = NULL;
	ft_fillco(s, c, cosize, p);
	return (p);
}
