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

void	first_child(pipex)
{
	dup2(pipex.pipe[1], 1);
	close(pipex.pipe[0]);
}

void	second_child(pipex)
{
	dup2(pipex.pipe[0], 0);
	close(pipex.pipe[0]);
}
