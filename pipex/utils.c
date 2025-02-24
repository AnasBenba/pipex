#include "pipex.h"

size_t	ft_strlen(const char *c)
{
	size_t	len;

	len = 0;
    if (!c)
    {
        return (0);
    }
	while (c[len])
		len++;
	return (len);
}

int	ft_isprint(int c)
{
	if (c >= 32 && c <= 126)
		return (1);
	return (0);
}

void	handling_errors(const char *msg)
{
	perror(msg);
	exit(1);
}

void	free_arr(char **arr)
{
	int	i = 0;
	if (!arr)
		return;
	while (arr[i])
		free(arr[i++]);
	free(arr);
}
