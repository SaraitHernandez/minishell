/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_strings.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sarherna <sarait.hernandez@novateva.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 15:38:38 by sarherna          #+#    #+#             */
/*   Updated: 2024/11/30 19:52:25 by sarherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*concat_content(char *existing, char *new_line)
{
	char	*result;

	if (!existing)
		return (ft_strdup(new_line));
	result = malloc(strlen(existing) + strlen(new_line) + 2);
	if (!result)
	{
		free_all(2, FREE_STRING, existing, FREE_STRING, new_line);
		exit_with_error("Memory allocation failed");
	}
	strcpy(result, existing);
	strcat(result, " ");
	strcat(result, new_line);
	free_all(2, FREE_STRING, existing, FREE_STRING, new_line);
	return (result);
}
