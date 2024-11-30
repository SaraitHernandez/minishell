/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akacprzy <akacprzy@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/17 22:16:24 by akacprzy          #+#    #+#             */
/*   Updated: 2024/11/24 19:43:37 by akacprzy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	bin_env(t_env *env)
{
	while (env && env->next != NULL)
	{
		ft_putstr_fd(env->key, 1);
		write(1, "=", 1);
		ft_putendl_fd(env->value, 1);
		env = env->next;
	}
	if (env)
	{
		ft_putstr_fd(env->key, 1);
		write(1, "=", 1);
		ft_putendl_fd(env->value, 1);
	}
	return (SUCCESS);
}
