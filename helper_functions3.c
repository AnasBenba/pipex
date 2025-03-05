/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_functions3.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenba <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 14:49:01 by abenba            #+#    #+#             */
/*   Updated: 2025/03/05 14:49:03 by abenba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	cmd_not_found(char **cmd_path, char **cmd, char *path)
{
	ft_free(cmd_path);
	ft_free(cmd);
	free(path);
	error_message("Commend not found");
}

void	free_all(char **cmd_path, char **cmd, char *path)
{
	ft_free(cmd_path);
	ft_free(cmd);
	free(path);
}

void	is_qou(char **ptr, char const *s, int i, size_t *y)
{
	(*ptr)[*y] = s[i];
	(*y)++;
}
