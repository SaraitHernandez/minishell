/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tests_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sarherna <sarait.hernandez@novateva.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 21:00:49 by sarherna          #+#    #+#             */
/*   Updated: 2024/11/30 00:21:56 by sarherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_tokens(t_token *tokens)
{
	printf("Token list:\n");
	while (tokens)
	{
		if (tokens->type == TOKEN_EOF)
			printf("TOKEN_EOF\n");
		else
			printf("%s: \"%s\"\n",
				token_type_to_string(tokens->type),
				tokens->value);
		tokens = tokens->next;
	}
	printf("\n");
}

void	print_ast_recursive(t_ast *ast, int depth)
{
	int	i;

	if (!ast)
		return ;
	print_indentation(depth);
	printf("%s\n", ast_type_to_string(ast->type));
	if (ast->type == NODE_COMMAND)
	{
		i = 0;
		while (ast->argv[i] != NULL)
		{
			print_indentation(depth + 1);
			printf("ARG[%d]: %s\n", i, ast->argv[i]);
			i++;
		}
	}
	else if (ast->type == NODE_REDIRECTION || ast->type == NODE_HEREDOC)
	{
		print_indentation(depth + 1);
		printf("Filename/Delimeter: %s\n", ast->filename);
		printf("Red. Type: %s\n", redirect_type_to_string(ast->redirect_type));
		printf("Red. Content: %s\n", ast->heredoc_content);
	}
	print_ast_recursive(ast->left, depth + 1);
	print_ast_recursive(ast->right, depth + 1);
}

void	print_ast(t_ast *ast)
{
	printf("AST:\n");
	print_ast_recursive(ast, 0);
	printf("\n");
}
