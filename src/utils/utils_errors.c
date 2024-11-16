/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_errors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sarherna <sarait.hernandez@novateva.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 11:35:46 by sarherna          #+#    #+#             */
/*   Updated: 2024/11/16 12:03:23 by sarherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	display_error(char *message)
{
	if (message)
		fprintf(stderr, "%s\n", message);
}

void	exit_with_error(char *message, int exit_code)
{
	if (message)
		fprintf(stderr, "%s\n", message);
	exit(exit_code);
}

void	comand_not_found(char *cmd_name)
{
	if (cmd_name)
		fprintf(stderr, "command not found:  %s\n", cmd_name);
}
