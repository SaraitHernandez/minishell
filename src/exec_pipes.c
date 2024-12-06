/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akacprzy <akacprzy@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 02:20:39 by akacprzy          #+#    #+#             */
/*   Updated: 2024/12/06 04:05:22 by akacprzy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ppx_pipe(t_ast *ast, t_shell *shell)
{
	int		fd[2];
	pid_t	pid;
	int		status;

	shell->in_pipe = 1;
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
		execute_ast(ast->left, shell);
		free_all(1, FREE_AST, ast);
		free_env_list(shell->env_list);
		exit(EXIT_SUCCESS);
	}
	else
	{
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
		execute_ast(ast->right, shell);
		waitpid(pid, &status, 0);
		if (WIFEXITED(status))
			shell->exit_status = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
			shell->exit_status = 128 + WTERMSIG(status);
		else if (WIFSTOPPED(status))
			shell->exit_status = 128 + WSTOPSIG(status);
		else
			shell->exit_status = status;
	}
}
