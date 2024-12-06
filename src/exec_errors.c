/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_errors.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akacprzy <akacprzy@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 03:03:00 by akacprzy          #+#    #+#             */
/*   Updated: 2024/12/06 01:45:17 by akacprzy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ppx_error(int errn)
{
	perror("minishell");
	exit(errn);
}

void	ppx_error_path(int errn, char *cmd)
{
	ft_putstr_fd("minishell: ", STDERR_FD);
	ft_putstr_fd(cmd, STDERR_FD);
	ft_putendl_fd(": No such file or directory", STDERR_FD);
	exit(errn);
}

void	ppx_error_cmd_not_found(int errn, char *cmd)
{
	ft_putstr_fd(cmd, STDERR_FD);
	ft_putendl_fd(": command not found", STDERR_FD);
	exit(errn);
}
