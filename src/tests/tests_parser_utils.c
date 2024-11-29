/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tests_parser_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sarherna <sarait.hernandez@novateva.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 22:17:13 by sarherna          #+#    #+#             */
/*   Updated: 2024/11/24 22:19:39 by sarherna         ###   ########.fr       */
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
	return ("UNKNOWN_TOKEN");
}

const char	*ast_type_to_string(t_ast_type type)
{
	if (type == NODE_COMMAND)
		return ("NODE_COMMAND");
	if (type == NODE_PIPE)
		return ("NODE_PIPE");
	if (type == NODE_REDIRECTION)
		return ("NODE_REDIRECTION");
	if (type == NODE_HEREDOC)
		return ("NODE_HEREDOC");
	return ("UNKNOWN_NODE");
}

const char	*redirect_type_to_string(int redirect_type)
{
	if (redirect_type == O_RDONLY)
		return ("O_RDONLY");
	else if (redirect_type == (O_WRONLY | O_CREAT | O_TRUNC))
		return ("O_WRONLY | O_CREAT | O_TRUNC");
	else if (redirect_type == (O_WRONLY | O_CREAT | O_APPEND))
		return ("O_WRONLY | O_CREAT | O_APPEND");
	else if (redirect_type == TOKEN_HEREDOC)
		return ("TOKEN_HEREDOC");
	else
		return ("UNKNOWN_REDIRECT_TYPE");
}

void	print_indentation(int depth)
{
	while (depth-- > 0)
		printf("    ");
}
