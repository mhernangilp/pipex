/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhernang <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/17 16:59:44 by mhernang          #+#    #+#             */
/*   Updated: 2023/10/01 19:03:37 by mhernang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex_bonus.h"

void	close_all(t_pipex *pipex)
{
	int	i;

	i = -1;
	while (++i < (pipex -> argc - 4))
	{
		close(pipex -> pipe[i][0]);
		close(pipex -> pipe[i][1]);
	}
}
