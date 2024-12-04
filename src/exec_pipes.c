/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akacprzy <akacprzy@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 02:20:39 by akacprzy          #+#    #+#             */
/*   Updated: 2024/12/04 01:02:47 by akacprzy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ppx_pipe(t_ast *ast, t_env *env, int *ret)
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
		close(fd[1]);
		get_ast_node(ast->left, env, ret);
		exit(EXIT_SUCCESS);
	}
	else
	{
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
		get_ast_node(ast->right, env, ret);
		waitpid(pid, NULL, 0);
	}
}
