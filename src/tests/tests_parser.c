/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tests_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sarherna <sarait.hernandez@novateva.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 21:00:49 by sarherna          #+#    #+#             */
/*   Updated: 2024/12/01 21:19:24 by sarherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_tokens(t_token *tokens)
{
	printf("Tokens:\n\n");
	while (tokens)
	{
		if (tokens->type == TOKEN_EOF)
			printf("TOKEN_EOF\n");
		else
		{
			printf("%s, value: %s\n",
				token_type_to_string(tokens->type),
				tokens->value);
		}
		tokens = tokens->next;
	}
	printf("\n");
}


void	print_redirections(t_red *redirs, int depth)
{
	while (redirs)
	{
		print_indentation(depth);
		printf("{ type: %s, filename: \"%s\" }\n",
			token_type_to_string(redirs->type),
			redirs->filename);
		redirs = redirs->next;
	}
}

void	print_command_node(t_ast *ast, int depth)
{
	int	i;

	print_indentation(depth + 1);
	printf("argv: [");
	for (i = 0; ast->argv && ast->argv[i]; i++)
	{
		printf("\"%s\"", ast->argv[i]);
		if (ast->argv[i + 1])
			printf(", ");
	}
	printf("]\n");
	if (ast->redirections)
	{
		print_indentation(depth + 1);
		printf("redirections:\n");
		print_redirections(ast->redirections, depth + 2);
	}
}

void	print_ast_recursive(t_ast *ast, int depth)
{
	if (!ast)
		return;
	print_indentation(depth);
	if (ast->type == NODE_COMMAND)
	{
		printf("Command Node:\n");
		print_command_node(ast, depth);
	}
	else if (ast->type == NODE_PIPE)
	{
		printf("Pipe Node:\n");
		print_indentation(depth + 1);
		printf("Left:\n");
		print_ast_recursive(ast->left, depth + 2);
		print_indentation(depth + 1);
		printf("Right:\n");
		print_ast_recursive(ast->right, depth + 2);
	}
}

void	print_ast(t_ast *ast)
{
	printf("AST Structure:\n\n");
	print_ast_recursive(ast, 0);
}
