/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sarherna <sarherna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 15:38:38 by sarherna          #+#    #+#             */
/*   Updated: 2024/12/08 22:09:12 by sarherna         ###   ########.fr       */
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
				status = handle_single_heredoc(redir, shell, ast);
				if (status)
					return (status);
			}
			redir = redir->next;
		}
	}
	else if (ast->type == NODE_PIPE)
		return (process_pipe_heredocs(ast, shell));
	return (0);
}

static int	process_line(char **line, t_red *redir, t_shell *shell, int expand)
{
	char	*expanded_line;

	if (!(*line))
		return (0);
	if (ft_strcmp(*line, redir->filename) == 0)
	{
		free(*line);
		return (0);
	}
	if (expand)
	{
		expanded_line = expand_variable(*line, shell);
		free(*line);
		if (!expanded_line)
        	return (0);
		*line = expanded_line;
	}
	return (1);
}

void	handle_heredoc_child(t_red *redir, t_shell *shell, int write_fd)
{
	char	*line;
	int		expand;

	expand = !redir->quoted;
	while (1)
	{
		if (g_signal_received == SIGINT)
		{

			break ;
		}
            
		line = readline("> ");
		if (!line)
        	break ;
		if (!process_line(&line, redir, shell, expand))
            break ;
		write(write_fd, line, ft_strlen(line));
		write(write_fd, "\n", 1);
		free(line);
	}
	close(write_fd);
}
