/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sarherna <sarait.hernandez@novateva.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 13:47:00 by sarherna          #+#    #+#             */
/*   Updated: 2024/12/01 21:25:50 by sarherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#define MAX_ARGS 50

t_ast	*parse_tokens(t_token *tokens)
{
	t_ast	*ast;

	ast = parse_pipeline(&tokens);
	return (ast);
}

t_ast	*parse_pipeline(t_token **tokens)
{
	t_ast	*left;
	t_ast	*right;

	left = parse_simple_command(tokens);
	while (*tokens && (*tokens)->type == TOKEN_PIPE)
	{
		*tokens = (*tokens)->next;
		right = parse_simple_command(tokens);
		if (!right)
		{
			display_error("Missing command after pipe");
			return (NULL);
		}
		left = create_pipe_node(left, right);
	}
	return (left);
}

t_ast	*parse_simple_command(t_token **tokens)
{
	t_ast	*cmd;
	char	*argv_local[MAX_ARGS];
	int		argc;
	t_red	*redirs;

	argc = 0;
	redirs = NULL;
	if (!parse_command_elements(tokens, argv_local, &argc, &redirs))
		return (NULL);
	argv_local[argc] = NULL;
	if (argc == 0 && !redirs)
		return (NULL);
	cmd = create_command_node(argv_local, argc, redirs);
	return (cmd);
}

int	parse_command_elements(t_token **tokens, char **argv_local,
	int *argc, t_red **redirs)
{
	while (*tokens && ((*tokens)->type == TOKEN_WORD
			|| is_redirection((*tokens)->type)))
	{
		if ((*tokens)->type == TOKEN_WORD && *argc < (MAX_ARGS - 1))
			parse_word_token(tokens, argv_local, argc);
		else if (is_redirection((*tokens)->type))
		{
			if (!parse_redirection_token(tokens, redirs))
				return (0);
		}
		else
			*tokens = (*tokens)->next;
	}
	return (1);
}
