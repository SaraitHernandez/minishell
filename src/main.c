/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sarherna <sarait.hernandez@novateva.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 11:58:33 by sarherna          #+#    #+#             */
/*   Updated: 2024/11/16 17:42:25 by sarherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_env	*env_list;

	(void)argc;
	(void)argv;
	//init_signal_handlers();
	init_shell_env(envp, &env_list);
	//shell_loop(env_list);
	free_env_list(env_list);
	return (0);
}
