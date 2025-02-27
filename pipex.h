#ifndef PIPEX_H
#define PIPEX_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/wait.h>

int		error_message(char *str);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
size_t	ft_strlen(const char *c);
char	*ft_strdup(const char *s1);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	**ft_split(char const *s);
int		ft_isspace(char c);
char	*ft_strjoin(char const *s1, char const *s2);
int		ft_isprint(int c);
char	*ft_strchr(const char *s, int c);


#endif