/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_errors.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akacprzy <akacprzy@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 03:03:00 by akacprzy          #+#    #+#             */
/*   Updated: 2024/12/07 00:50:13 by akacprzy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ppx_error(int errn)
{
	perror("minishell");
	exit(errn);
}

void	ppx_error_path(int errn, t_ast *ast, t_env *env, t_past *past)
{
	ft_putstr_fd("minishell: ", STDERR_FD);
	ft_putstr_fd(ast->argv[0], STDERR_FD);
	ft_putendl_fd(": No such file or directory", STDERR_FD);
	if (past == NULL)
		free_all(1, FREE_AST, ast);
	else
		clear_past(past);
	free_env_list(env);
	exit(errn);
}

void	ppx_error_cmd_not_found(int errn, t_ast *ast, t_env *env, t_past *past)
{
	ft_putstr_fd(ast->argv[0], STDERR_FD);
	ft_putendl_fd(": command not found", STDERR_FD);
	if (past == NULL)
		free_all(1, FREE_AST, ast);
	else
		clear_past(past);
	free_env_list(env);
	exit(errn);
}
