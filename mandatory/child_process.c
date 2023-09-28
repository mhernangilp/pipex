/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_process.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhernang <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 16:03:52 by mhernang          #+#    #+#             */
/*   Updated: 2023/09/17 17:14:38 by mhernang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

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

	pipex.in = open(argv[1], O_RDONLY);
	if (pipex.in < 0)
		error_msg("Infile error");
	dup2(pipex.pipe[1], 1);
	dup2(pipex.in, 0);
	close(pipex.pipe[0]);
	close(pipex.in);
	close(pipex.out);
	arguments = ft_split(argv[2], ' ');
	command = get_command(pipex.paths, arguments[0]);
	if (!command)
		error_msg("Error with command");
	if (execve(command, arguments, envp) < 0)
		exit(1);
}

void	second_child(t_pipex pipex, char **argv, char **envp)
{
	char	*command;
	char	**arguments;

	pipex.out = open(argv[4], O_CREAT | O_WRONLY | O_TRUNC, 0666);
	if (pipex.out < 0)
		error_msg("Outfile error");
	dup2(pipex.pipe[0], 0);
	dup2(pipex.out, 1);
	close(pipex.pipe[1]);
	close(pipex.in);
	close(pipex.out);
	arguments = ft_split(argv[3], ' ');
	command = get_command(pipex.paths, arguments[0]);
	if (!command)
		error_msg("Error with command");
	if (execve(command, arguments, envp) < 0)
		exit(1);
}
