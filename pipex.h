/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhernang <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 18:47:39 by mhernang          #+#    #+#             */
/*   Updated: 2023/06/21 18:47:40 by mhernang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include             <stdio.h>
# include <unistd.h>
# include <sys/wait.h>


//Child process
void	child_process(void);

//Parent process
void	parent_process(void);

#endif
