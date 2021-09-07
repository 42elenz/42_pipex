#ifndef PIPEX_H
# define PIPEX_H

# include "../libft/libft.h"
# include <sys/wait.h>
# include <fcntl.h>
# include <errno.h>
# include <string.h>

char	*ft_get_path(char *com, char **env);
void	ft_childprocess(char **argv, char **env, int *fd);
void	ft_execute(char *argv, char **env);
char	*ft_get_path(char *com, char **env);
void	ft_error(void);
int		ft_check_argv(char *argv);

#endif