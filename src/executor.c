/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akacprzy <akacprzy@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 03:02:54 by akacprzy          #+#    #+#             */
/*   Updated: 2024/12/08 15:40:38 by akacprzy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	retain_stds(int *saved_stdin, int *saved_stdout)
{
	*saved_stdin = dup(STDIN_FILENO);
	*saved_stdout = dup(STDOUT_FILENO);
}

static void	restore_stds(int *saved_stdin, int *saved_stdout)
{
	dup2(*saved_stdin, STDIN_FILENO);
	dup2(*saved_stdout, STDOUT_FILENO);
	close(*saved_stdin);
	close(*saved_stdout);
}

void	execute_ast(t_ast *ast, t_shell *shell)
{
	t_red	*cred;
	int		saved_stdin;
	int		saved_stdout;

	if (!ast)
		return ;
	retain_stds(&saved_stdin, &saved_stdout);
	if (ast->type == NODE_COMMAND)
	{
		cred = ast->redirections;
		while (cred != NULL)
		{
			if (handle_redirection(cred) != 0)
			{
				shell->exit_status = 1;
				restore_stds(&saved_stdin, &saved_stdout);
				return ;
			}
			cred = cred->next;
		}
		if (ast->argv[0])
		{
			if (is_builtin(ast->argv[0]) == 1)
				exec_builtin(ast->argv, shell);
			else
				ppx_child(ast, shell);
		}
	}
	else if (ast->type == NODE_PIPE)
		ppx_pipe(ast, shell);
	restore_stds(&saved_stdin, &saved_stdout);
}
