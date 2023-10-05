/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhernang <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 18:47:39 by mhernang          #+#    #+#             */
/*   Updated: 2023/09/17 17:17:17 by mhernang         ###   ########.fr       */
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
	pid_t	pid1;
	pid_t	pid2;
	int		pipe[2];
	int		in;
	int		out;
	char	**paths;
}	t_pipex;

//child_process
void	first_child(t_pipex pipex, char **argv, char **envp);
void	second_child(t_pipex pipex, char **argv, char **envp);

//libft
int		ft_strncmp(char *s1, char *s2, unsigned int n);
char	**ft_split(char const *s, char c);
char	*ft_strjoin(char const *s1, char const *s2);

//error
void	error_msg(char *err);

#endif
