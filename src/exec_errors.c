/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_errors.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sarherna <sarherna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 03:03:00 by akacprzy          #+#    #+#             */
/*   Updated: 2024/12/08 12:39:36 by sarherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ppx_error(int errn, t_ast *ast, t_env *env)
{
	perror("minishell");
	free_all(1, FREE_AST, ast);
	free_env_list(env);
	exit(errn);
}

void	ppx_error_path(int errn, t_ast *ast, t_env *env)
{
	ft_putstr_fd("minishell: ", STDERR_FD);
	ft_putstr_fd(ast->argv[0], STDERR_FD);
	ft_putendl_fd(": No such file or directory", STDERR_FD);
	free_all(1, FREE_AST, ast);
	free_env_list(env);
	exit(errn);
}

void	ppx_error_cmd_not_found(int errn, t_ast *ast, t_env *env)
{
	ft_putstr_fd(ast->argv[0], STDERR_FD);
	ft_putendl_fd(": command not found", STDERR_FD);
	free_all(1, FREE_AST, ast);
	free_env_list(env);
	exit(errn);
}
