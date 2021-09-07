#include "../includes/pipex.h"

/* 
** Define the input-file as input and the output as the beginning of the
** pipe. WRITING END OF THE PIPE
 */
void	ft_childprocess(char **argv, char **env, int *fd)
{
	int	in_file;

	in_file = open(argv[1], O_RDONLY, 0777);
	if (in_file < 0)
		ft_error();
	dup2(in_file, STDIN_FILENO);
	dup2(fd[1], STDOUT_FILENO);
	close(fd[0]);
	ft_execute(argv[2], env);
}

/* 
** Define the output as outfile and the pipe part fd[0] as 
** Rewire the whole pipe. READING END OF THE PIPE
 */
void	ft_mainprocess(char **argv, char **env, int *fd)
{
	int	out_file;

	out_file = open(argv[4], O_WRONLY | O_TRUNC | O_CREAT, 0777);
	if (out_file < 0)
		ft_error();
	dup2(fd[0], STDIN_FILENO);
	dup2(out_file, STDOUT_FILENO);
	close(fd[1]);
	ft_execute(argv[3], env);
}

/* 
** Main: 
** Is the argc ok?
** create pipes
** start the child and the parent
** close all pipes.
 */
int	main(int argc, char **argv, char **env)
{
	int	fd[2];
	int	pid;

	if (argc != 5)
	{
		ft_putstr_fd("Exactly 5 args needed", 2);
		return (1);
	}
	else
	{
		if (pipe(fd) == -1)
			ft_error();
		pid = fork();
		if (pid < 0)
			ft_error();
		if (pid == 0)
			ft_childprocess(argv, env, fd);
		else
			ft_mainprocess(argv, env, fd);
		wait(NULL);
		close(fd[0]);
		close(fd[1]);
	}
	return (0);
}
