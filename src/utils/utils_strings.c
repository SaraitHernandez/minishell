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

char	*concat_content(char *existing, char *new_line)
{
	char	*result;

	if (!existing)
		return (strdup(new_line));
	result = malloc(strlen(existing) + strlen(new_line) + 2);
	if (!result)
	{
		free(existing);
		free(new_line);
		exit_with_error("Memory allocation failed during heredoc concatenation");
	}
	strcpy(result, existing);
    strcat(result, " ");
	strcat(result, new_line);
	free(existing);
	free(new_line);
	return (result);
}