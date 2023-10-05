/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_process.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhernang <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 16:03:52 by mhernang          #+#    #+#             */
/*   Updated: 2023/10/01 18:51:30 by mhernang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex_bonus.h"
#include <unistd.h>

static char	*get_command(char **paths, char *file)
{
	char	*command;
	char	*temp;

	if (access(file, F_OK | X_OK) == 0)
		return (file);
	if (paths)
	{
		while (*paths)
		{
			temp = ft_strjoin(*paths, "/");
			command = ft_strjoin(temp, file);
			free(temp);
			if (access(command, F_OK | X_OK) == 0)
				return (command);
			free(command);
			paths++;
		}
	}
	return (NULL);
}

void	first_child(t_pipex pipex, char **argv, char **envp)
{
	char	*command;
	char	**arguments;

	set_infile(&pipex, argv);
	dup2(pipex.in, 0);
	dup2(pipex.pipe[0][1], 1);
	close_all(&pipex);
	if (pipex.here_doc == 0)
		arguments = ft_split(argv[2], ' ');
	else
		arguments = ft_split(argv[3], ' ');
	command = get_command(pipex.paths, arguments[0]);
	if (!command)
		error_msg("Error with command");
	if (execve(command, arguments, envp) < 0)
		exit(1);
}

void	middle_child(t_pipex pipex, char **argv, char **envp, int pipe)
{
	char	*command;
	char	**arguments;

	dup2(pipex.pipe[pipe][0], 0);
	dup2(pipex.pipe[pipe + 1][1], 1);
	close_all(&pipex);
	arguments = ft_split(argv[pipe + 3], ' ');
	command = get_command(pipex.paths, arguments[0]);
	if (!command)
		error_msg("Error with command");
	if (execve(command, arguments, envp) < 0)
		exit(1);
}

void	last_child(t_pipex pipex, char **argv, char **envp, int pipe)
{
	char	*command;
	char	**arguments;

	if (pipex.here_doc == 0)
		pipex.out = open(argv[pipex.argc - 1], O_CREAT | O_WRONLY
		   | O_TRUNC, 0666);
	else
		pipex.out = open(argv[5], O_CREAT | O_WRONLY | O_APPEND, 0666);
	if (pipex.out < 0)
		error_msg("Outfile error");
	dup2(pipex.pipe[pipe][0], 0);
	dup2(pipex.out, 1);
	close_all(&pipex);
	if (pipex.here_doc == 0)
		arguments = ft_split(argv[pipex.argc - 2], ' ');
	else
		arguments = ft_split(argv[4], ' ');
	command = get_command(pipex.paths, arguments[0]);
	if (!command)
		error_msg("Error with command");
	if (execve(command, arguments, envp) < 0)
		exit(1);
}
