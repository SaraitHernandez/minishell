/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akacprzy <akacprzy@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 02:20:39 by akacprzy          #+#    #+#             */
/*   Updated: 2024/12/10 01:19:38 by akacprzy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ppx_pipe_left(t_ast *ast, t_shell *shell)
{
	t_ast	*tmp;

	tmp = ast->left;
	free_ast(ast->right);
	free(ast);
	execute_ast(tmp, shell, NULL);
	free_ast(tmp);
	free_env_list(shell->env_list);
	exit(EXIT_SUCCESS);
}

void	ppx_pipe(t_ast *ast, t_shell *shell)
{
	int		fd[2];
	pid_t	pid;
	int		status;

	shell->in_pipe = 1;
	if (pipe(fd) == -1)
		ppx_error(EXIT_FAILURE, ast, shell->env_list, NULL);
	pid = fork();
	if (pid == -1)
		ppx_error(EXIT_FAILURE, ast, shell->env_list, NULL);
	if (pid == 0)
	{
		close(fd[0]);
		dup2(fd[1], STDOUT_FILENO);
		close(fd[1]);
		ppx_pipe_left(ast, shell);
	}
	else
	{
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
		execute_ast(ast->right, shell, ast);
		waitpid(pid, &status, 0);
	}
}
