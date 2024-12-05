/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akacprzy <akacprzy@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/17 22:16:30 by akacprzy          #+#    #+#             */
/*   Updated: 2024/12/05 00:59:30 by akacprzy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	bin_exit(char **args, t_shell *shell)
{
	if (shell->in_pipe == 0)
	{
		shell->do_exit = 1;
		ft_putstr_fd("exit\n", STDERR_FD);
	}
	if (args[1] && args[2])
	{
		shell->do_exit = 0;
		shell->exit_status = 1;
		ft_putendl_fd("minishell: exit: too many arguments", STDERR_FD);
	}
	else if (args[1] && ft_strisnum(args[1]) == 0)
	{
		shell->exit_status = 255;
		ft_putstr_fd("minishell: exit: ", STDERR_FD);
		ft_putstr_fd(args[1], STDERR_FD);
		ft_putendl_fd(": numeric argument required", STDERR_FD);
	}
	else if (args[1])
		shell->exit_status = ft_atoi(args[1]);
}
