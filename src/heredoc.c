/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sarherna <sarait.hernandez@novateva.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 15:38:38 by sarherna          #+#    #+#             */
/*   Updated: 2024/12/04 14:55:53 by sarherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	process_pipe_heredocs(t_ast *ast, t_shell *shell)
{
	if (process_heredocs(ast->left, shell) != 0)
		return (1);
	if (process_heredocs(ast->right, shell) != 0)
		return (1);
	return (0);
}

int	process_heredocs(t_ast *ast, t_shell *shell)
{
	int		status;
	t_red	*redir;

	if (!ast)
		return (0);
	if (ast->type == NODE_COMMAND)
	{
		redir = ast->redirections;
		while (redir)
		{
			if (redir->type == TOKEN_HEREDOC)
			{
				status = handle_single_heredoc(redir, shell);
				if (status != 0)
					return (status);
			}
			redir = redir->next;
		}
	}
	else if (ast->type == NODE_PIPE)
		return (process_pipe_heredocs(ast, shell));
	return (0);
}
