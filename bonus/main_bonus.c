/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhernang <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 18:47:31 by mhernang          #+#    #+#             */
/*   Updated: 2023/10/01 18:58:00 by mhernang         ###   ########.fr       */
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

static void	initialize_pipex(t_pipex *pipex)
{
	int	i;

	pipex -> pipe = malloc((pipex -> argc - 4) * sizeof(int *));
	if (!(pipex -> pipe))
		exit_msg("Error allocating memory\n");
	i = -1;
	while (++i < (pipex -> argc - 4))
	{
		pipex -> pipe[i] = malloc(2 * sizeof(int));
		if (!(pipex -> pipe[i]))
			exit_msg("Error allocating memory\n");
		if (pipe(pipex -> pipe[i]) < 0)
			exit_msg("Error creating pipes\n");
	}
	pipex -> pid = malloc((pipex -> argc - 3) * sizeof(pid_t));
}

static void	wait_all(t_pipex *pipex)
{
	int	i;

	i = -1;
	while (++i < (pipex -> argc) - 3)
	{
		waitpid(pipex -> pid[i], NULL, 0);
	}
}

static void	check_here_doc(t_pipex *pipex, char **argv, int argc)
{
	if (!ft_strncmp("here_doc\0", argv[1], 9))
	{
		pipex -> here_doc = 1;
		if (argc != 6)
			exit_msg("Invalid number of arguments");
		pipex -> argc = 5;
	}
	else
	{
		pipex -> here_doc = 0;
		pipex -> argc = argc;
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_pipex	pipex;
	int		i;

	if (argc < 5)
		exit_msg("Invalid number of arguments");
	check_here_doc(&pipex, argv, argc);
	initialize_pipex(&pipex);
	pipex.paths = get_paths(envp);
	pipex.pid[0] = fork();
	if (pipex.pid[0] == 0)
		first_child(pipex, argv, envp);
	i = 0;
	while (++i < pipex.argc - 4)
	{
		pipex.pid[i] = fork();
		if (pipex.pid[i] == 0)
			middle_child(pipex, argv, envp, i - 1);
	}
	pipex.pid[pipex.argc - 4] = fork();
	if (pipex.pid[pipex.argc - 4] == 0)
		last_child(pipex, argv, envp, pipex.argc - 5);
	close_all(&pipex);
	wait_all(&pipex);
	if (pipex.here_doc == 1)
		unlink(".heredoc");
	exit (0);
}
