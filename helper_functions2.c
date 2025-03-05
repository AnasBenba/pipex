/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_functions2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenba <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 14:45:16 by abenba            #+#    #+#             */
/*   Updated: 2025/03/05 14:45:18 by abenba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*get_path(char **envp)
{
	char	*path;
	int		i;

	path = NULL;
	i = 0;
	if (envp[0] == NULL)
		path = ft_strdup("/home/abenba/bin:/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:/usr/games:/usr/local/games:/snap/bin");
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
			path = ft_substr(envp[i], 5, ft_strlen(envp[i]));
		i++;
	}
	if (path == NULL)
		error_message("Error retriving the path");
	return (path);
}

void	path_input(char **cmd, char **cmd_path, char **envp, char *path)
{
	if (access(cmd[0], X_OK) == 0)
	{
		execve(cmd[0], cmd, envp);
		free_all(cmd_path, cmd, path);
		error_message("execve Error:");
	}
}

void	exec_cmd(char **cmd_path, char **envp, char *path, char **cmd)
{
	char	*tmp;
	char	*full_path;
	int		i;

	i = 0;
	tmp = NULL;
	full_path = NULL;
	while (cmd_path[i])
	{
		tmp = ft_strjoin(cmd_path[i], "/");
		full_path = ft_strjoin(tmp, cmd[0]);
		free(tmp);
		if (access(full_path, X_OK) == 0)
		{
			execve(full_path, cmd, envp);
			free(full_path);
			free_all(cmd_path, cmd, path);
			error_message("execve Error:");
			break ;
		}
		free(full_path);
		i++;
	}
	if (!cmd_path[i])
		cmd_not_found(cmd_path, cmd, path);
}

void	execut_commend(char **av, char **envp)
{
	char	**cmd_path;
	char	*path;
	char	**cmd;

	path = get_path(envp);
	cmd_path = ft_split(path);
	if (!cmd_path)
	{
		free(path);
		error_message("Error happend while using split");
	}
	cmd = ft_split(av[2]);
	if (!cmd || !cmd[0] || cmd[0][0] == '\0')
		cmd_error(cmd, cmd_path, path);
	path_input(cmd, cmd_path, envp, path);
	exec_cmd(cmd_path, envp, path, cmd);
	free_all(cmd_path, cmd, path);
}

void	execut_commend2(char **av, char **envp)
{
	char	*path;
	char	**cmd_path;
	char	**cmd;

	path = get_path(envp);
	cmd_path = ft_split(path);
	if (!cmd_path)
	{
		free(path);
		error_message("Error happend while using split");
	}
	cmd = ft_split(av[3]);
	if (!cmd || !cmd[0] || cmd[0][0] == '\0')
		cmd_error(cmd, cmd_path, path);
	path_input(cmd, cmd_path, envp, path);
	exec_cmd(cmd_path, envp, path, cmd);
	free_all(cmd_path, cmd, path);
}
