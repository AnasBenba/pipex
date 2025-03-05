/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenba <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 14:52:13 by abenba            #+#    #+#             */
/*   Updated: 2025/03/05 14:52:20 by abenba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <unistd.h>

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
int		ft_strcmp(const char *s1, const char *s2);
void	close_fds(int fds[], int pip[]);
void	fd_0_error(int pip[]);
void	fd_1_error(int fd[], int pip[]);
void	fork_error(int fds[], int pip[]);
void	cmd_error(char **cmd, char **cmd_path, char *path);
void	ft_free(char **ptr);
void	cmd_not_found(char **cmd_path, char **cmd, char *path);
void	free_all(char **cmd_path, char **cmd, char *path);
char	*get_path(char **envp);
void	path_input(char **cmd, char **cmd_path, char **envp, char *path);
void	exec_cmd(char **cmd_path, char **envp, char *path, char **cmd);
void	execut_commend(char **av, char **envp);
void	execut_commend2(char **av, char **envp);
void	is_qou(char **ptr, char const *s, int i, size_t *y);

#endif
