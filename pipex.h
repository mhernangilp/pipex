/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhernang <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 18:47:39 by mhernang          #+#    #+#             */
/*   Updated: 2023/07/12 11:08:47 by mhernang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include             <stdio.h>
# include <unistd.h>
# include <sys/wait.h>
# include <fcntl.h>

typedef struct	s_pipex
{
	pid_t	pid1;
	pid_t	pid2;
	int		pipe[2];
	int		in;
	int		out;
	char	**paths;
}	t_pipex;

//child_process
void	first_child(pipex);
void	second_child(pipex);

//utils
int	ft_strncmp(char *s1, char *s2, unsigned int n);

#endif
