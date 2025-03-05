/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenba <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 14:42:19 by abenba            #+#    #+#             */
/*   Updated: 2025/03/05 14:42:21 by abenba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	fd_0_error(int pip[])
{
	close(pip[0]);
	close(pip[1]);
	error_message("Error");
}

void	fd_1_error(int fd[], int pip[])
{
	close(fd[0]);
	close(pip[0]);
	close(pip[1]);
	error_message("Error:");
}

void	fork_error(int fds[], int pip[])
{
	close_fds(fds, pip);
	error_message("Fork Error:");
}

void	cmd_error(char **cmd, char **cmd_path, char *PATH)
{
	ft_free(cmd_path);
	ft_free(cmd);
	free(PATH);
	error_message("Error happend while using split");
}
