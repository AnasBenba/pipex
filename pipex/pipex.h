#ifndef PIPEX_H
# define PIPEX_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <stdio.h>
# include <string.h>

size_t	ft_strlen(const char *c);
void	handling_errors(const char *msg);
int     ft_isprint(int c);
char	*get_cmd_path(char *cmd, char **envp);
void	free_arr(char **arr);
char	**ft_split(char const *s, char c);
char	*ft_strjoin(char const *s1, char const *s2);

#endif