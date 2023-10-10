
#include "../includes/pipex_bonus.h"

static void	load_heredoc(char *arg)
{
	char	*buf;
	int	fd;

	fd = open(".heredoc", O_WRONLY | O_CREAT | O_TRUNC, 0666);
	if (fd < 0)
		error_msg("Heredoc error");
	while (1)
	{
		write(1, "heredoc> ", 9);
		buf = get_next_line(0);
		if (!buf)
			exit_msg("Heredoc read error");
		if (!ft_strncmp(arg, buf, ft_strlen(arg) + 1))
			break ;
		write(fd, buf, ft_strlen(buf));
		free(buf);
	}
	close(fd);
	free(buf);
}

void	set_infile(t_pipex *pipex, char **argv)
{
	if (pipex ->  here_doc == 1)
	{
		load_heredoc(ft_strjoin(argv[2], "\n"));
		pipex -> in = open(".heredoc", O_RDONLY);
	}
	else
		pipex -> in = open(argv[1], O_RDONLY);
	if (pipex -> in < 0)
	{
		if (pipex -> here_doc == 1)
			unlink(".heredoc");
		error_msg("Infile error");
	}
}
