
#include "../includes/pipex_bonus.h"
#include <unistd.h>

static void	load_heredoc(t_pipex *pipex, char *arg)
{
	char	*buf;
	pid_t	pid;
	int	fd[2];

	if (pipe(fd) < 0)
		error_msg("Error creating pipe");
	pid = fork();
	if (pid == 0)
	{
		close(fd[0]);
		write(1, "heredoc> ", 9);
		buf = get_next_line(0);
		while (buf)
		{
			if (!ft_strncmp(arg, buf, ft_strlen(arg) + 1))
				break ;
			write(fd[1], buf, ft_strlen(buf));
			free(buf);
			write(1, "heredoc> ", 9);
			buf = get_next_line(0);
		}
		close(fd[1]);
		free(buf);
	}
	else 
	{
		close(fd[1]);
		pipex -> in = fd[0];
		wait(NULL);
	}
}

void	set_infile(t_pipex *pipex, char **argv)
{
	if (pipex ->  here_doc == 1)
		load_heredoc(pipex, ft_strjoin(argv[2], "\n"));
	else
	{
		pipex -> in = open(argv[1], O_RDONLY);
		if (pipex -> in < 0)
			error_msg("Infile error");
	}
}
