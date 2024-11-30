/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enviroment_variables.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akacprzy <akacprzy@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 16:34:55 by sarherna          #+#    #+#             */
/*   Updated: 2024/11/24 22:20:31 by akacprzy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ensure_path_variable(t_env *env)
{
	if (!get_env_value("PATH", env))
		set_env_value("PATH", "/usr/bin:/bin", &env);
}
