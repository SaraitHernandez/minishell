/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sarherna <sarait.hernandez@novateva.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 13:47:00 by sarherna          #+#    #+#             */
/*   Updated: 2024/11/24 19:41:01 by sarherna         ###   ########.fr       */
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
	t_ast	*pipe_node;

	left = parse_command(tokens);
	while (*tokens && (*tokens)->type == TOKEN_PIPE)
	{
		*tokens = (*tokens)->next;
		right = parse_command(tokens);
		if (!right)
            display_error("Missing command after pipe");
		pipe_node = malloc(sizeof(t_ast));
		if (!pipe_node)
			exit_with_error("Memory allocation failed");
		pipe_node->type = NODE_PIPE;
		pipe_node->argv = NULL;
        pipe_node->filename = NULL;
        pipe_node->redirect_type = 0;
		pipe_node->left = left;
		pipe_node->right = right;
		left = pipe_node;
	}
	return (left);
}

char **copy_argv(char **argv_local, int argc)
{
    char **argv;
    int i;

    argv = malloc(sizeof(char *) * (argc + 1));
    if (!argv)
        exit_with_error("Memory allocation failed for argv");

    i = 0;
    while (i < argc)
    {
        argv[i] = argv_local[i];
        i++;
    }
    argv[i] = NULL;

    return argv;
}

t_ast	*parse_command(t_token **tokens)
{
	t_ast		*cmd;
	char		*argv_local[MAX_ARGS];
	int			argc;
	char 		**argv;

	
	argc = 0;
	while (*tokens && (*tokens)->type == TOKEN_WORD && argc < (MAX_ARGS - 1))
	{
		argv_local[argc++] = (*tokens)->value;
		*tokens = (*tokens)->next;
	}
	argv_local[argc] = NULL;
	argv = copy_argv(argv_local, argc);
	cmd = create_command_node(argv);
	cmd = parse_redirections(cmd, tokens);
	return (cmd);
}

t_ast	*parse_redirections(t_ast *cmd, t_token **tokens)
{
	t_token_type	type;
	char			*file;

	while (*tokens && is_redirection((*tokens)->type))
	{
		type = (*tokens)->type;
		*tokens = (*tokens)->next;
		if (!*tokens || (*tokens)->type != TOKEN_WORD)
			display_error("Missing file for redirection");
		file = (*tokens)->value;
		*tokens = (*tokens)->next;
		cmd = create_redirection_node(cmd, type, file);
	}
	return (cmd);
}
