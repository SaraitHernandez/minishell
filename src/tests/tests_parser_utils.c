/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tests_parser_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sarherna <sarait.hernandez@novateva.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 22:17:13 by sarherna          #+#    #+#             */
/*   Updated: 2024/12/01 21:17:16 by sarherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

const char	*token_type_to_string(t_token_type type)
{
	if (type == TOKEN_WORD)
		return ("TOKEN_WORD");
	if (type == TOKEN_PIPE)
		return ("TOKEN_PIPE");
	if (type == TOKEN_REDIRECT_IN)
		return ("TOKEN_REDIRECT_IN");
	if (type == TOKEN_REDIRECT_OUT)
		return ("TOKEN_REDIRECT_OUT");
	if (type == TOKEN_REDIRECT_APPEND)
		return ("TOKEN_REDIRECT_APPEND");
	if (type == TOKEN_HEREDOC)
		return ("TOKEN_HEREDOC");
	if (type == TOKEN_EOF)
		return ("TOKEN_EOF");
	return ("UNKNOWN_TOKEN");
}

void	print_indentation(int depth)
{
	while (depth-- > 0)
		printf("    ");
}
