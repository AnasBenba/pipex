#include "pipex.h"

void ft_free(char **str)
{
	int i;
	
	i = 0;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
}

void execut_commend(char **av, char **envp)
{
	char *PATH;
	char **cmd_path;
	char *full_path;
	char *tmp;
	char **cmd;
	int i;
	
	PATH = NULL;
	i = 0;

	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
			PATH = ft_substr(envp[i], 5, ft_strlen(envp[i]));
		i++;
	}
	if (PATH == NULL)
		error_message("Error retriving the path");
	cmd_path = ft_split(PATH);
	if (!cmd_path)
	{
		free(PATH);
		error_message("Error happend while using split");
	}
	cmd = ft_split(av[2]);
	if (!cmd || !cmd[0] || cmd[0][0] == '\0')
	{
		ft_free(cmd_path);
		ft_free(cmd);
		free(PATH);
		error_message("Error happend while using split");
	}
	i = 0;
	while (cmd_path[i])
	{
		tmp = ft_strjoin(cmd_path[i], "/");
		full_path = ft_strjoin(tmp, cmd[0]);
		free(tmp);

		if (access(full_path, X_OK) == 0 || access(cmd[0], X_OK) == 0)
		{
			execve(full_path, cmd, envp);
			free(full_path);
			ft_free(cmd_path);
			ft_free(cmd);
			free(PATH);
			error_message("execve Error:");
			break;
		}
		free(full_path);
		i++;
	}
	if (!cmd_path[i])
	{
		ft_free(cmd_path);
		ft_free(cmd);
		free(PATH);
		error_message("Commend not found");
	}
	ft_free(cmd_path);
    ft_free(cmd);
    free(PATH);
}

void execut_commend2(char **av, char **envp)
{
	char *PATH;
	char **cmd_path;
	char *full_path;
	char *tmp;
	char **cmd;
	int i;
	
	PATH = NULL;
	i = 0;

	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
			PATH = ft_substr(envp[i], 5, ft_strlen(envp[i]));
		i++;
	}
	if (PATH == NULL)
		error_message("Error retriving the path");
	cmd_path = ft_split(PATH);
	if (!cmd_path)
	{
		free(PATH);
		error_message("Error happend while using split");
	}
	cmd = ft_split(av[3]);
	if (!cmd || !cmd[0] || cmd[0][0] == '\0')
	{
		ft_free(cmd_path);
		ft_free(cmd);
		free(PATH);
		error_message("Error happend while using split");
	}
	i = 0;
	while (cmd_path[i])
	{
		tmp = ft_strjoin(cmd_path[i], "/");
		full_path = ft_strjoin(tmp, cmd[0]);
		free(tmp);

		if (access(full_path, X_OK) == 0 || access(cmd[0], X_OK) == 0)
		{
			execve(full_path, cmd, envp);
			free(full_path);
			ft_free(cmd_path);
			ft_free(cmd);
			free(PATH);
			error_message("execve Error:");
			break;
		}
		free(full_path);
		i++;
	}
	if (!cmd_path[i])
	{
		ft_free(cmd_path);
		ft_free(cmd);
		free(PATH);
		error_message("Commend not found");
	}
	ft_free(cmd_path);
	ft_free(cmd);
	free(PATH);
}

void child_process1(char **av, int *fds, int *pip, char **envp)
{
	dup2(fds[0], 0);
	dup2(pip[1], 1);
	close(fds[0]);
	close(pip[0]);
	close(fds[1]);
	close(pip[1]);
	execut_commend(av, envp);
}


void child_process2(char **av, int *fds, int *pip, char **envp)
{
	dup2(fds[1], 1);
	dup2(pip[0], 0);
	close(fds[0]);
	close(pip[0]);
	close(fds[1]);
	close(pip[1]);
	execut_commend2(av, envp);
}

int main(int ac, char **av, char **envp)
{
	int fds[2];
	int pip[2];
	int id1;
	int id2;

    if (ac != 5)
		error_message("Usage: ./pipex file1 cmd1 cmd2 file2");
	if (pipe(pip) == -1)
		error_message("Pipe Error");
	fds[0] = open(av[1], O_RDONLY);
	if (fds[0] == -1)
	{
		close(pip[0]);
		close(pip[1]);
		error_message("Error");
	}
	fds[1] = open(av[4], O_WRONLY | O_CREAT | O_TRUNC , 0644);
	if (fds[1] == -1)
	{
		close(fds[0]);
		close(pip[0]);
		close(pip[1]);
		error_message("Error:");
	}
	id1 = fork();
	if (id1 == -1)
	{
		close(fds[0]);
		close(fds[1]);
		close(pip[0]);
		close(pip[1]);
		error_message("Fork Error:");
	}
	if (id1 == 0)
		child_process1(av, fds, pip, envp);
	waitpid(id1, NULL, 0);
	id2 = fork();
	if (id2 == -1)
	{
		close(fds[0]);
		close(fds[1]);
		close(pip[0]);
		close(pip[1]);
		error_message("Fork Error:");
	}
	if (id2 == 0)
		child_process2(av, fds, pip, envp);
	waitpid(id2, NULL, 0);
	close(fds[0]);
	close(fds[1]);
	close(pip[0]);
	close(pip[1]);
	return (0);
}