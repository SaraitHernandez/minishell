/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akacprzy <akacprzy@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 02:20:39 by akacprzy          #+#    #+#             */
/*   Updated: 2024/12/07 02:24:44 by akacprzy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_past	*create_past_node(t_ast *ast)
{
	t_past	*node;

	node = malloc(sizeof(t_past));
	if (!node)
		exit_with_error("Memory allocation failed");
	node->ast = ast;
	node->next = NULL;
	return (node);
}

void	add_past_node(t_past **past, t_ast *ast)
{
	t_past	*current;

	if (!*past)
		*past = create_past_node(ast);
	else
	{
		current = *past;
		while (current->next)
			current = current->next;
		current->next = create_past_node(ast);
	}
}

void	clear_past(t_past *past)
{
	if (!past)
		return ;
	clear_past(past->next);
	free_ast(past->ast);
	free(past);
}

void	ppx_pipe(t_ast *ast, t_shell *shell, t_past *past)
{
	int		fd[2];
	pid_t	pid;
	int		status;

	shell->in_pipe = 1;
	add_past_node(&past, ast);
	if (pipe(fd) == -1)
		ppx_error(EXIT_FAILURE);
	pid = fork();
	if (pid == -1)
		ppx_error(EXIT_FAILURE);
	// add_past_node(&past, ast);
	if (pid == 0)
	{
		close(fd[0]);
		dup2(fd[1], STDOUT_FILENO);
		close(fd[1]);
		// add_past_node(&past, ast);
		execute_ast(ast->left, shell, past);
		free_env_list(shell->env_list);
		clear_past(past);
		exit(EXIT_SUCCESS);
	}
	else
	{
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
		execute_ast(ast->right, shell, past);
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
