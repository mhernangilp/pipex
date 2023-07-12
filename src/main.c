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

static char	*get_path(char **envp)
{
	int	i;

	i = -1;
	while (envp[++i] != NULL)
	{
		if (!ft_strncmp("PATH", envp[i], 4))
			return (&envp[i][5]);
	}
	return (NULL);
}

int	main(int argc, char **argv, char **envp)
{
	t_pipex	pipex;
	char	*path;

	if (argc != 5)
		return(1);
	pipex.in = open(argv[1], O_RDONLY);
	if (pipex.in < 0)
		return(2);
	pipex.out = open(argv[4], O_CREAT | O_RDWR, 0777);
	if (pipex.out < 0)
		return(3);
	if (pipe(pipex.pipe) < 0)
		return(4);
	path = get_path(envp);
	pipex.pid1 = fork();
	if (pipex.pid1 == 0)
		first_child(pipex);
	pipex.pid2 = fork();
	if (pipex.pid2 == 0)
		second_child(pipex);
	close(pipex.pipe[0]);
	close(pipex.pipe[1]);
	waitpid(pipex.pid1, NULL, 0);
	waitpid(pipex.pid2, NULL, 0);
	return (0);
}
