/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akacprzy <akacprzy@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 02:20:39 by akacprzy          #+#    #+#             */
/*   Updated: 2024/12/01 15:18:36 by akacprzy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ppx_child(char **argv, t_env *env)
{
	int		fd[2];
	pid_t	pid;

	if (pipe(fd) == -1)
		ppx_error(EXIT_FAILURE);
	pid = fork();
	if (pid == -1)
		ppx_error(EXIT_FAILURE);
	if (pid == 0)
	{
		close(fd[0]);
		dup2(fd[1], STDOUT_FILENO);
		ppx_cmd_exec(argv, env);
	}
	else
	{
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
		waitpid(pid, NULL, WNOHANG);
	}
}

