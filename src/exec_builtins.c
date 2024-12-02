/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtins.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akacprzy <akacprzy@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 03:03:00 by akacprzy          #+#    #+#             */
/*   Updated: 2024/12/01 15:42:22 by akacprzy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		is_builtin(char *cmd)
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
	return (0);
}

int		exec_builtin(char **args, t_env *env)
{
	int	ret;

	ret = 0;
	if (ft_strcmp(args[0], "pwd") == 0)
		ret = bin_pwd();
	if (ft_strcmp(args[0], "cd") == 0)
		ret = bin_cd(args, env);
	if (ft_strcmp(args[0], "echo") == 0)
		ret = bin_echo(args);
	if (ft_strcmp(args[0], "env") == 0)
		ret = bin_env(env);
	if (ft_strcmp(args[0], "export") == 0)
		ret = bin_export(args, env);
	if (ft_strcmp(args[0], "unset") == 0)
		ret = bin_unset(args, env);
	return (ret);
}
