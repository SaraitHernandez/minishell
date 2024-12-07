/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sarherna <sarherna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 02:20:39 by akacprzy          #+#    #+#             */
/*   Updated: 2024/12/07 17:15:27 by sarherna         ###   ########.fr       */
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
		ppx_error(EXIT_FAILURE, ast, shell->env_list);
	pid = fork();
	if (pid == -1)
		ppx_error(EXIT_FAILURE, ast, shell->env_list);
	if (pid == 0)
	{
		close(fd[0]);
		dup2(fd[1], STDOUT_FILENO);
		close(fd[1]);
		execute_ast(ast->left, shell);
		free_ast(ast);
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
	}
}
