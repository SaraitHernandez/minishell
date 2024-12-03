/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_nodes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sarherna <sarait.hernandez@novateva.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 20:55:03 by sarherna          #+#    #+#             */
/*   Updated: 2024/12/03 16:48:22 by sarherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_redirection(t_token_type type)
{
	return (type == TOKEN_REDIRECT_IN
		|| type == TOKEN_REDIRECT_OUT
		|| type == TOKEN_REDIRECT_APPEND
		|| type == TOKEN_HEREDOC);
}

t_red	*create_redirection_node(t_token_type type, char *filename, int quoted)
{
	t_red	*redir;

	redir = malloc(sizeof(t_red));
	if (!redir)
		exit_with_error("Memory allocation failed");
	redir->type = type;
	redir->filename = filename;
	redir->quoted = quoted;
	redir->next = NULL;
	return (redir);
}

t_ast	*create_command_node(char **argv_local, int argc, t_red *redirs)
{
	t_ast	*cmd;

	cmd = malloc(sizeof(t_ast));
	if (!cmd)
		exit_with_error("Memory allocation failed");
	cmd->type = NODE_COMMAND;
	cmd->argv = copy_argv(argv_local, argc);
	cmd->redirections = redirs;
	cmd->left = NULL;
	cmd->right = NULL;
	return (cmd);
}

t_ast	*create_pipe_node(t_ast *left, t_ast *right)
{
	t_ast	*pipe_node;

	pipe_node = malloc(sizeof(t_ast));
	if (!pipe_node)
		exit_with_error("Memory allocation failed");
	pipe_node->type = NODE_PIPE;
	pipe_node->argv = NULL;
	pipe_node->redirections = NULL;
	pipe_node->left = left;
	pipe_node->right = right;
	return (pipe_node);
}
