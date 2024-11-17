/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sarherna <sarait.hernandez@novateva.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 15:38:38 by sarherna          #+#    #+#             */
/*   Updated: 2024/11/17 18:53:07 by sarherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_shell_env(char **envp, t_env **env_list)
{
	*env_list = copy_environment(envp);
	ensure_path_variable(*env_list);
	set_shell_level(env_list);
}

void	set_shell_level(t_env **env)
{
	char	*level_str;
	int		level;
	char	*old_level_str;

	old_level_str = get_env_value("SHLVL", *env);
	if (old_level_str)
		level = ft_atoi(old_level_str) + 1;
	else
		level = 1;
	level_str = ft_itoa(level);
	set_env_value("SHLVL", level_str, env);
	free(level_str);
}
