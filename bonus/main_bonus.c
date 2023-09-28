/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhernang <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 18:47:31 by mhernang          #+#    #+#             */
/*   Updated: 2023/09/17 17:13:04 by mhernang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex_bonus.h"
#include <stdio.h>

static char	**get_paths(char **envp)
{
	int		i;
	char	*path;
	char	**paths;

	path = NULL;
	if (!envp)
		return (NULL);
	i = -1;
	while (envp[++i] != NULL)
	{
		if (!ft_strncmp("PATH=", envp[i], 5))
			path = (&envp[i][5]);
	}
	if (!path)
		return (NULL);
	paths = ft_split(path, ':');
	return (paths);
}

static void	close_all(t_pipex *pipex)
{
	close(pipex -> pipe[0]);
	close(pipex -> pipe[1]);
	close(pipex -> in);
	close(pipex -> out);
}

int	main(int argc, char **argv, char **envp)
{
	t_pipex	pipex;

	if (argc != 5)
		error_msg("Invalid number of arguments");
	if (pipe(pipex.pipe) < 0)
		error_msg("Pipe creation error");
	pipex.paths = get_paths(envp);
	pipex.pid1 = fork();
	if (pipex.pid1 == 0)
		first_child(pipex, argv, envp);
	pipex.pid2 = fork();
	if (pipex.pid2 == 0)
		second_child(pipex, argv, envp);
	close_all(&pipex);
	waitpid(pipex.pid1, NULL, 0);
	waitpid(pipex.pid2, NULL, 0);
	return (0);
}
