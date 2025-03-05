/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenba <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 14:50:34 by abenba            #+#    #+#             */
/*   Updated: 2025/03/05 14:50:35 by abenba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	child_process1(char **av, int *fds, int *pip, char **envp)
{
	dup2(fds[0], 0);
	dup2(pip[1], 1);
	close(fds[0]);
	close(pip[0]);
	close(fds[1]);
	close(pip[1]);
	execut_commend(av, envp);
}

void	child_process2(char **av, int *fds, int *pip, char **envp)
{
	dup2(fds[1], 1);
	dup2(pip[0], 0);
	close(fds[0]);
	close(pip[0]);
	close(fds[1]);
	close(pip[1]);
	execut_commend2(av, envp);
}

void	close_fds(int fds[], int pip[])
{
	close(fds[0]);
	close(fds[1]);
	close(pip[0]);
	close(pip[1]);
}

void	pipex(int *fds, int *pip, char **av, char **envp)
{
	int	id1;
	int	id2;

	id1 = fork();
	if (id1 == -1)
		fork_error(fds, pip);
	if (id1 == 0)
		child_process1(av, fds, pip, envp);
	id2 = fork();
	if (id2 == -1)
		fork_error(fds, pip);
	if (id2 == 0)
		child_process2(av, fds, pip, envp);
	close_fds(fds, pip);
	waitpid(id1, NULL, 0);
	waitpid(id2, NULL, 0);
}

int	main(int ac, char **av, char **envp)
{
	int	fds[2];
	int	pip[2];

	if (ac < 4 || ac > 5)
		error_message("Usage: ./pipex file1 cmd1 cmd2 file2");
	if (pipe(pip) == -1)
		error_message("Pipe Error");
	fds[0] = open(av[1], O_RDONLY);
	if (fds[0] == -1)
		fd_0_error(pip);
	if (ac == 5)
		fds[1] = open(av[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else
		fds[1] = open("outfile", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fds[1] == -1)
		fd_1_error(fds, pip);
	pipex(fds, pip, av, envp);
	return (0);
}
