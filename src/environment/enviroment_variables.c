/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enviroment_variables.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sarherna <sarait.hernandez@novateva.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 16:34:55 by sarherna          #+#    #+#             */
/*   Updated: 2024/11/16 17:31:44 by sarherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ensure_path_variable(t_env *env)
{
	if (!get_env_value("PATH", env))
		set_env_value("PATH", "/usr/bin:/bin", env);
}
