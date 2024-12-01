/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sarherna <sarait.hernandez@novateva.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 20:08:41 by sarherna          #+#    #+#             */
/*   Updated: 2024/12/01 21:24:34 by sarherna         ###   ########.fr       */
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

int	process_heredoc(t_ast *ast, t_token *tokens, char *input)
{
	t_ast	*heredoc_node;
	t_ast	*last_child;
	int		heredoc_status;
	
	(void)heredoc_node;
	heredoc_node = NULL;
	last_child = last_left_child(ast);
	heredoc_status = 0;
	if (ast->type == NODE_HEREDOC)
		heredoc_node = ast;
	else if (last_child && last_child->type == NODE_HEREDOC)
		heredoc_node = last_child;
	//if (heredoc_node)
	//	heredoc_status = handle_heredoc(heredoc_node, tokens, ast);
	if (heredoc_status == 1)
	{
		free_all(3, FREE_STRING, input, FREE_TOKEN, tokens, FREE_AST, ast);
		return (1);
	}
	return (0);
}

void	debug_print(t_token *tokens, t_ast *ast)
{
	print_tokens(tokens);
	print_ast(ast);
}
