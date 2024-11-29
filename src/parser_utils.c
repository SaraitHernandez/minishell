/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sarherna <sarait.hernandez@novateva.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 14:15:42 by sarherna          #+#    #+#             */
/*   Updated: 2024/11/24 20:54:47 by sarherna         ###   ########.fr       */
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

t_ast	*create_command_node(char **argv)
{
	t_ast	*cmd;

	cmd = malloc(sizeof(t_ast));
	if (!cmd)
		exit_with_error("Memory allocation failed");
	cmd->type = NODE_COMMAND;
	cmd->argv = argv;
	cmd->left = NULL;
	cmd->right = NULL;
	cmd->filename = NULL;
	cmd->heredoc_content = NULL;
	cmd->redirect_type = 0;
	return (cmd);
}

t_ast	*create_redirection_node(t_ast *cmd, t_token_type type, char *file)
{
	t_ast	*redir;

	redir = malloc(sizeof(t_ast));
	if (!redir)
		exit_with_error("Memory allocation failed");
	if (type == TOKEN_HEREDOC)
		redir->type = NODE_HEREDOC;
	else
		redir->type = NODE_REDIRECTION;
	redir->filename = ft_strdup(file);
	if (type == TOKEN_REDIRECT_IN)
		redir->redirect_type = O_RDONLY;
	else if (type == TOKEN_REDIRECT_OUT)
		redir->redirect_type = O_WRONLY | O_CREAT | O_TRUNC;
	else if (type == TOKEN_REDIRECT_APPEND)
		redir->redirect_type = O_WRONLY | O_CREAT | O_APPEND;
	else if (type == TOKEN_HEREDOC)
		redir->redirect_type = TOKEN_HEREDOC;
	redir->left = cmd;
	redir->right = NULL;
	redir->argv = NULL;
	redir->heredoc_content = NULL;
	return (redir);
}

char	**copy_argv(char **argv_local, int argc)
{
	char	**argv;
	int		i;

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
	return (argv);
}

t_ast	*last_left_child(t_ast *ast)
{
	if (!ast)
		return (NULL);
	while (ast->left)
		ast = ast->left;
	return (ast);
}