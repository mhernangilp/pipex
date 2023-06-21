/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhernang <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 18:47:31 by mhernang          #+#    #+#             */
/*   Updated: 2023/06/21 18:47:32 by mhernang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

int	main(int argc, char **argv)
{
	int	pid;

	(void)argc;
	(void)argv;

	pid = fork();
	if (pid == 0)
		printf("Hago primer comando\n");
	if (pid != 0)
		wait(NULL);
	if (pid != 0)
		printf("Hago segundo comando\n");
	return (0);
}
