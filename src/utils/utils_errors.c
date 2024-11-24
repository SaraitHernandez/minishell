/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_errors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sarherna <sarait.hernandez@novateva.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 11:35:46 by sarherna          #+#    #+#             */
/*   Updated: 2024/11/24 13:43:42 by sarherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	display_error(char *message)
{
	if (message)
		fprintf(stderr, "%s\n", message);
}

void	exit_with_error(char *message)
{
	if (message)
		fprintf(stderr, "%s\n", message);
	exit(EXIT_FAILURE);
}

void	comand_not_found(char *cmd_name)
{
	if (cmd_name)
		fprintf(stderr, "command not found:  %s\n", cmd_name);
}
