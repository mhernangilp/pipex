/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhernang <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 18:47:31 by mhernang          #+#    #+#             */
/*   Updated: 2023/10/29 19:22:52 by mhernang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex_bonus.h"

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

static void	initialize_pipex(t_pipex *pipex, int argc)
{
	int	i;

	pipex -> pipe = malloc((argc - 4) * sizeof(int *));
	if (!(pipex -> pipe))
		exit_msg("Error allocating memory\n");
	i = -1;
	while (++i < (argc - 4))
	{
		pipex -> pipe[i] = malloc(2 * sizeof(int));
		if (!(pipex -> pipe[i]))
			exit_msg("Error allocating memory\n");
		if (pipe(pipex -> pipe[i]) < 0)
			exit_msg("Error creating pipes\n");
	}
	pipex -> pid = malloc((argc - 3) * sizeof(pid_t));
}

void close_all(t_pipex *pipex)
{
	int i;

	i = -1;
	while (++i < (pipex -> argc - 4))
	{
		close(pipex -> pipe[i][0]);
		close(pipex -> pipe[i][1]);
	}
}

static void wait_all(t_pipex *pipex)
{
	int i;

	i = -1;
	while (++i < (pipex -> argc) - 3)
	{
		waitpid(pipex -> pid[i], NULL, 0);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_pipex	pipex;

	if (argc != 5)
		exit_msg("Invalid number of arguments");
	pipex.argc = argc;
	initialize_pipex(&pipex, argc);
	pipex.paths = get_paths(envp);
	pipex.pid[0] = fork();
	if (pipex.pid[0] == 0)
		first_child(pipex, argv, envp);
	pipex.pid[argc - 4] = fork();
	if (pipex.pid[argc - 4] == 0)
		last_child(pipex, argv, envp, argc - 5);
	close_all(&pipex);
	wait_all(&pipex);
	exit (0);
}
