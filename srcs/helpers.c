#include "../includes/pipex.h"

/* 
** ERROR FUNCTION TO PRINT ERRORS IN THE ERROROUTPUT
 */
void	ft_error(void)
{
	ft_putstr_fd(strerror(errno), 2);
	ft_putstr_fd("\n", 2);
	exit(EXIT_FAILURE);
}

/*
** DOES MY ARGV ALREADY CONTAIN THE ABSOLUTE PATH?
*/
int	ft_check_argv(char *argv)
{
	char	**com_matrix2;

	com_matrix2 = ft_split(argv, ' ');
	if (access(com_matrix2[0], X_OK) == 0)
	{
		free(com_matrix2);
		return (1);
	}
	else
	{
		free(com_matrix2);
		return (0);
	}
}

/* 
** Looking for PATH= in my env, and then splitting the pathes.
** Then adding Slash, joining it with my commmand and see if it's
** executable.
 */
char	*ft_get_path(char *com, char **env)
{
	int		i;
	int		j;
	char	**possible_path;
	char	*path;
	char	*path_slash;

	i = 0;
	j = 0;
	while (env[i] != NULL)
	{
		if (ft_strncmp(env[i], "PATH=", 5) == 0)
			break ;
		i++;
	}
	possible_path = ft_split(env[i] + 5, ':');
	while (possible_path[j] != NULL)
	{
		path_slash = ft_strjoin(possible_path[j], "/");
		path = ft_strjoin(path_slash, com);
		free(path_slash);
		if (access(path, X_OK) == 0)
			return (path);
		j++;
	}
	return (NULL);
}

/* 
** Execute the argv in the env.
 */
void	ft_execute(char *argv, char **env)
{
	char	*path;
	char	**com_matrix;
	int		check;

	check = ft_check_argv(argv);
	if (check == 1)
	{
		com_matrix = ft_split(argv, ' ');
		if (execve(com_matrix[0], com_matrix, env) < 0)
			ft_error();
	}
	else
	{
		com_matrix = ft_split(argv, ' ');
		path = ft_get_path(com_matrix[0], env);
		if (path == NULL)
		{
			ft_putstr_fd("command not found: ", 2);
			ft_putstr_fd(argv, 2);
			ft_putstr_fd("\n", 2);
			exit(EXIT_FAILURE);
		}
		if (execve(path, com_matrix, env) < 0)
			ft_error();
	}
}
