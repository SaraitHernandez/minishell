/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akacprzy <akacprzy@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 03:02:54 by akacprzy          #+#    #+#             */
/*   Updated: 2024/12/04 01:48:58 by akacprzy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	get_ast_node(t_ast *ast, t_env *env, int *ret)
{
	t_red	*cred;

	if (!ast)
		return ;
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
}
