/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akacprzy <akacprzy@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/17 22:16:42 by akacprzy          #+#    #+#             */
/*   Updated: 2024/11/28 02:16:59 by akacprzy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	bin_unset(char **args, t_env *env)
{
	int	i;

	if (!(args[1]))
		return (SUCCESS);
	i = 1;
	while (args[i])
	{
		unset_env_value(args[i], env);
		i++;
	}
	return (SUCCESS);
}
