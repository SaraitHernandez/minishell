/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sarherna <sarait.hernandez@novateva.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 20:08:41 by sarherna          #+#    #+#             */
/*   Updated: 2024/12/02 21:23:23 by sarherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_interrupt(char *input)
{
	if (g_signal_received == SIGINT)
	{
		g_signal_received = 0;
		free_all(1, FREE_STRING, input);
		return (1);
	}
	return (0);
}

int	check_ast_null(char *input, t_token *tokens, t_ast *ast)
{
	if (ast == NULL)
	{
		free_all(2, FREE_STRING, input, FREE_TOKEN, tokens);
		return (1);
	}
	return (0);
}

void	debug_print(t_token *tokens, t_ast *ast)
{
	print_tokens(tokens);
	print_ast(ast);
}
