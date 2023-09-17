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
# include <stdlib.h>

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
void	first_child(t_pipex pipex, char **paths, char **argv, char **envp);
void	second_child(t_pipex pipex, char **paths, char **argv, char **envp);

//utils
int	ft_strncmp(char *s1, char *s2, unsigned int n);
char	**ft_split(char const *s, char c);

//utils_2
char	*ft_strjoin(char const *s1, char const *s2);

#endif
