/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtins.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akacprzy <akacprzy@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 03:03:00 by akacprzy          #+#    #+#             */
/*   Updated: 2024/12/05 01:08:55 by akacprzy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_builtin(char *cmd)
{
	if (ft_strcmp(cmd, "pwd") == 0)
		return (1);
	if (ft_strcmp(cmd, "cd") == 0)
		return (1);
	if (ft_strcmp(cmd, "echo") == 0)
		return (1);
	if (ft_strcmp(cmd, "env") == 0)
		return (1);
	if (ft_strcmp(cmd, "export") == 0)
		return (1);
	if (ft_strcmp(cmd, "unset") == 0)
		return (1);
	if (ft_strcmp(cmd, "exit") == 0)
		return (1);
	return (0);
}

void	exec_builtin(char **args, t_shell *shell)
{
	if (ft_strcmp(args[0], "pwd") == 0)
		shell->exit_status = bin_pwd();
	if (ft_strcmp(args[0], "cd") == 0)
		shell->exit_status = bin_cd(args, shell->env_list);
	if (ft_strcmp(args[0], "echo") == 0)
		shell->exit_status = bin_echo(args);
	if (ft_strcmp(args[0], "env") == 0)
		shell->exit_status = bin_env(shell->env_list);
	if (ft_strcmp(args[0], "export") == 0)
		bin_export(args, shell);
	if (ft_strcmp(args[0], "unset") == 0)
		shell->exit_status = bin_unset(args, shell->env_list);
	if (ft_strcmp(args[0], "exit") == 0)
		bin_exit(args, shell);
}
