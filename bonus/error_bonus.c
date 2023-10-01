/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhernang <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/01 18:21:59 by mhernang          #+#    #+#             */
/*   Updated: 2023/10/01 18:22:09 by mhernang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex_bonus.h"

void	error_msg(char *err)
{
	perror(err);
	exit (1);
}

void	exit_msg(char *msg)
{
	printf("%s\n", msg);
	exit(1);
}
