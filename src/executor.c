/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akacprzy <akacprzy@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 03:02:54 by akacprzy          #+#    #+#             */
/*   Updated: 2024/12/02 22:04:21 by akacprzy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_ast_node(t_ast *ast, t_env *env)
{
	int	file1;
	int	file2;
	int	ret;

	if (!ast)
		return (0);
	if (ast->type == NODE_COMMAND)
	{
		if (is_builtin(ast->argv[0]) == 1)
			ret = exec_builtin(ast->argv, env);
		else
			ret = ppx_cmd_exec(ast->argv, env);
	}
	else if (ast->type == NODE_PIPE)
	{
		// do what needs to be done for pipes
		ret = get_ast_node(ast->left, env);
		ret = get_ast_node(ast->right, env);
	}
	else if (ast->type == NODE_REDIRECTION)
	{
		
		if (ast->redirect_type == O_RDONLY)
		{
			file1 = ppx_fopen(ast->filename, 'r');
			ppx_infile_protector(&file1);
		}
		else if (ast->redirect_type == (O_WRONLY | O_CREAT | O_TRUNC))
		{
			file2 = ppx_fopen(ast->filename, 't');
			dup2(file2, STDOUT_FILENO);
		}
		else if (ast->redirect_type == (O_WRONLY | O_CREAT | O_APPEND))
		{
			file2 = ppx_fopen(ast->filename, 'a');
			dup2(file2, STDOUT_FILENO);
		}
	}
	else if (ast->type == NODE_HEREDOC)
	{
		ppx_here_doc(ast);
		ret = get_ast_node(ast->left, env);
	}
	return (ret);
}
