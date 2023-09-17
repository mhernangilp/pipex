/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhernang <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 18:47:31 by mhernang          #+#    #+#             */
/*   Updated: 2023/07/12 11:08:38 by mhernang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

static char	**get_paths(char **envp)
{
	int	i;
	char	*path;
	char	**paths;

	i = -1;
	while (envp[++i] != NULL)
	{
		if (!ft_strncmp("PATH", envp[i], 4))
			path = (&envp[i][5]);
	}
	if (!path)
		return (NULL);
	paths = ft_split(path, ':');
	return (paths);
}

int	main(int argc, char **argv, char **envp)
{
	t_pipex	pipex;
	char	**paths;

	if (argc != 5)
		return(1);
	pipex.in = open(argv[1], O_RDONLY);
	if (pipex.in < 0)
		return(2);
	pipex.out = open(argv[4], O_CREAT | O_WRONLY | O_TRUNC, 0666);
	if (pipex.out < 0)
		return(3);
	if (pipe(pipex.pipe) < 0)
		return(4);
	paths = get_paths(envp);
	pipex.pid1 = fork();
	if (pipex.pid1 == 0)
		first_child(pipex, paths, argv, envp);
	pipex.pid2 = fork();
	if (pipex.pid2 == 0)
		second_child(pipex, paths, argv, envp);
	close(pipex.pipe[0]);
	close(pipex.pipe[1]);
	waitpid(pipex.pid1, NULL, 0);
	waitpid(pipex.pid2, NULL, 0);
	return (0);
}
