/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhernang <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 18:47:39 by mhernang          #+#    #+#             */
/*   Updated: 2023/10/01 16:07:13 by mhernang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <stdlib.h>
# include <stdio.h>

typedef struct s_pipex
{
	pid_t	*pid;
	int		**pipe;
	int		in;
	int		out;
	int		argc;
	char	**paths;
}	t_pipex;

//main
void	close_all(t_pipex *pipex);

//child_process
void	first_child(t_pipex pipex, char **argv, char **envp);
void	middle_child(t_pipex pipex, char **argv, char **envp, int pipe);
void	last_child(t_pipex pipex, char **argv, char **envp, int pipe);

//utils
int		ft_strncmp(char *s1, char *s2, unsigned int n);
char	**ft_split(char const *s, char c);

//utils_2
char	*ft_strjoin(char const *s1, char const *s2);

//error
void	error_msg(char *err);
void	exit_msg(char *msg);

#endif
