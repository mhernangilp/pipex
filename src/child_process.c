/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_process.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhernang <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 16:03:52 by mhernang          #+#    #+#             */
/*   Updated: 2023/07/12 11:08:40 by mhernang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

static char	*get_command(char **paths, char *file)
{
	char	*command;
	char	*temp;

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
	return (NULL);
}

void	first_child(t_pipex pipex, char **paths, char **argv, char **envp)
{
	char	*command;
	char	**arguments;

	dup2(pipex.pipe[1], 1);
	dup2(pipex.in, 0);
	close(pipex.pipe[0]);
	arguments = ft_split(argv[2], ' ');
	command = get_command(paths, arguments[0]);
	if (!command)
		exit(5);
	execve(command, arguments, envp);
}

void	second_child(t_pipex pipex, char **paths, char **argv, char **envp)
{
	char	*command;
	char	**arguments;

	dup2(pipex.pipe[0], 0);
	dup2(pipex.out, 1);
	close(pipex.pipe[1]);
	arguments = ft_split(argv[3], ' ');
	command = get_command(paths, arguments[0]);
	if (!command)
		exit(6);
	execve(command, arguments, envp);
}
