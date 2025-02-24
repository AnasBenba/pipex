#include "pipex.h"

void	exec_cmd(char *cmd, char **envp)
{
	char	**args = ft_split(cmd, ' ');
	char	*cmd_path = get_cmd_path(args[0], envp);

	if (!cmd_path)
	{
		free_arr(args);
		handling_errors("Command not found");
	}
	if (execve(cmd_path, args, envp) == -1)
	{
		free(cmd_path);
		free_arr(args);
		handling_errors("Execve failed");
	}
}

void	child_process(char **argv, char **envp, int pipe_fd[2], int infile)
{
	dup2(infile, STDIN_FILENO);
	dup2(pipe_fd[1], STDOUT_FILENO);
	close(pipe_fd[0]);
	close(pipe_fd[1]);
	close(infile);
	exec_cmd(argv[2], envp);
}

void	parent_process(char **argv, char **envp, int pipe_fd[2], int outfile)
{
	dup2(pipe_fd[0], STDIN_FILENO);
	dup2(outfile, STDOUT_FILENO);
	close(pipe_fd[0]);
	close(pipe_fd[1]);
	close(outfile);
	exec_cmd(argv[3], envp);
}

int	main(int argc, char **argv, char **envp)
{
	int		infile, outfile;
	int		fd[2];
	pid_t	pid;

	if (argc != 5)
		handling_errors("Usage: ./pipex infile cmd1 cmd2 outfile");
	infile = open(argv[1], O_RDONLY);
	if (infile < 0)
		handling_errors("Infile open error");
	outfile = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC , 0644);
	if (outfile < 0)
		handling_errors("Outfile open error");
	if (pipe(fd) == -1)
		handling_errors("Pipe error");
	pid = fork();
	if (pid < 0)
		handling_errors("Fork error");
	if (pid == 0)
		child_process(argv, envp, fd, infile);
	close(fd[1]);
	waitpid(pid, NULL, 0);
	parent_process(argv, envp, fd, outfile);
	return (0);
}