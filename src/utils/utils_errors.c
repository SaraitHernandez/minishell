/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_errors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sarherna <sarait.hernandez@novateva.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 11:35:46 by sarherna          #+#    #+#             */
/*   Updated: 2024/12/01 11:26:21 by sarherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	display_error(char *message)
{
	if (message)
	{
		write(STDERR_FILENO, message, ft_strlen(message));
		write(STDERR_FILENO, "\n", 1);
	}
}

void	exit_with_error(char *message)
{
	if (message)
	{
		write(STDERR_FILENO, message, ft_strlen(message));
		write(STDERR_FILENO, "\n", 1);
	}
	exit(EXIT_FAILURE);
}

void	comand_not_found(char *cmd_name)
{
	if (cmd_name)
	{
		write(STDERR_FILENO, "command not found:  ", 20);
		write(STDERR_FILENO, cmd_name, ft_strlen(cmd_name));
		write(STDERR_FILENO, "\n", 1);
	}
}
