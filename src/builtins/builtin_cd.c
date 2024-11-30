/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akacprzy <akacprzy@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/17 22:13:39 by akacprzy          #+#    #+#             */
/*   Updated: 2024/11/27 00:20:18 by akacprzy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	cd_update_oldpwd(t_env *env)
{
	char	cwd[PATH_MAX];

	if (getcwd(cwd, PATH_MAX) == NULL)
		return (ERROR);
	set_env_value("OLDPWD", cwd, &env);
	return (SUCCESS);
}

static int	cd_update_pwd(t_env *env)
{
	char	cwd[PATH_MAX];

	if (getcwd(cwd, PATH_MAX) == NULL)
		return (ERROR);
	set_env_value("PWD", cwd, &env);
	return (SUCCESS);
}

static int	cd_go_to_path(int option, t_env *env)
{
	char	*env_path;
	int		ret;

	if (option == 0)
	{
		env_path = ft_strdup(get_env_value("HOME", env));
		if (!env_path)
		{
			ft_putendl_fd("minishell : cd: HOME not set", STDERR_FD);
			return (ERROR);
		}
	}
	else if (option == 1)
	{
		env_path = ft_strdup(get_env_value("OLDPWD", env));
		if (!env_path)
		{
			ft_putendl_fd("minishell : cd: OLDPWD not set", STDERR_FD);
			return (ERROR);
		}
	}
	cd_update_oldpwd(env);
	ret = chdir(env_path);
	free(env_path);
	return (ret);
}

static void	cd_error(char **args)
{
	ft_putstr_fd("minishell : cd: ", 2);
	ft_putstr_fd(strerror(errno), 2);
	ft_putstr_fd(": ", 2);
	ft_putendl_fd(args[1], 2);
}

int	bin_cd(char **args, t_env *env)
{
	int	ret;

	if (!args[1])
		ret = cd_go_to_path(0, env);
	else if (args[2])
	{
		ft_putendl_fd("minishell : cd: too many arguments", STDERR_FD);
		return (ERROR);
	}
	else if (ft_strcmp(args[1], "-") == 0)
		ret = cd_go_to_path(1, env);
	else
	{
		cd_update_oldpwd(env);
		ret = chdir(args[1]);
		if (ret < 0)
			ret *= -1;
		if (ret != 0)
			cd_error(args);
	}
	cd_update_pwd(env);
	return (ret);
}
