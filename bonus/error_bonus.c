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
