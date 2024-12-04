/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akacprzy <akacprzy@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 03:02:54 by akacprzy          #+#    #+#             */
/*   Updated: 2024/12/04 02:42:21 by akacprzy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	get_ast_node(t_ast *ast, t_env *env, int *ret)
{
	t_red	*cred;
	int	saved_stdin;
	int	saved_stdout;

	if (!ast)
		return ;
	saved_stdin = dup(STDIN_FILENO);
	saved_stdout = dup(STDOUT_FILENO);
	if (ast->type == NODE_COMMAND)
	{
		cred = ast->redirections;
		while (cred != NULL)
		{
			if (handle_redirection(cred) != 0)
				return ;
			cred = cred->next;
		}
		if (is_builtin(ast->argv[0]) == 1)
			exec_builtin(ast->argv, env, ret);
		else
			ppx_child(ast, env, ret);
	}
	else if (ast->type == NODE_PIPE)
		ppx_pipe(ast, env, ret);
	
	dup2(saved_stdin, STDIN_FILENO);
	dup2(saved_stdout, STDOUT_FILENO);
	close(saved_stdin);
	close(saved_stdout);
}
