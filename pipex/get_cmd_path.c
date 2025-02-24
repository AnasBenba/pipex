#include "pipex.h"

char	*get_cmd_path(char *cmd, char **envp)
{
	char	**paths;
	char	*path_env;
	char	*cmd_path;
	int		i;
    char *tmp;

	i = 0;
	while (envp[i] && strncmp(envp[i], "PATH=", 5) != 0)
		i++;
	if (!envp[i])
		return (NULL);
	path_env = envp[i] + 5;
	paths = ft_split(path_env, ':');
	if (!paths)
		return (NULL);
	i = 0;
	while (paths[i])
	{
		cmd_path = malloc(ft_strlen(paths[i]) + ft_strlen(cmd) + 2);
		if (!cmd_path)
			return (NULL);
        tmp = ft_strjoin(paths[i], "/");
        cmd_path = ft_strjoin(tmp, cmd);
        free(tmp);
		if (access(cmd_path, X_OK) == 0)
			return (free_arr(paths), cmd_path);
		free(cmd_path);
		i++;
	}
	return (free_arr(paths), NULL);
}
