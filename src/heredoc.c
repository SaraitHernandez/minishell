/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sarherna <sarait.hernandez@novateva.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 15:38:38 by sarherna          #+#    #+#             */
/*   Updated: 2024/12/04 08:10:38 by sarherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	write_line_to_pipe(char *line, int *pipe_fd)
{
	write(pipe_fd[1], line, ft_strlen(line));
	write(pipe_fd[1], "\n", 1);
}

static char	*process_line(char *line, t_shell *shell, int expand)
{
	char	*expanded_line;

	if (expand)
	{
		expanded_line = expand_variable(line, shell);
		free(line);
		return (expanded_line);
	}
	return (line);
}

static int	handle_heredoc_reading(t_red *redir, t_shell *shell,
			int *pipe_fd, int expand)
{
	char	*line;

	while (1)
	{
		line = readline("> ");
		if (!line || ft_strcmp(line, redir->filename) == 0)
			break ;
		line = process_line(line, shell, expand);
		write_line_to_pipe(line, pipe_fd);
		free(line);
	}
	free(line);
	close(pipe_fd[1]);
	return (g_signal_received == SIGINT);
}

int	handle_single_heredoc(t_red *redir, t_shell *shell)
{
	int		pipe_fd[2];
	int		expand;

	if (pipe(pipe_fd) == -1)
		return (display_error("Failed to create pipe"), 1);
	expand = !redir->quoted;
	setup_heredoc_signal_handlers();
	if (handle_heredoc_reading(redir, shell, pipe_fd, expand))
		return (handle_heredoc_interrupt(pipe_fd[0]));
	setup_signal_handlers();
	redir->fd = pipe_fd[0];
	return (0);
}

int	process_heredocs(t_ast *cmd, t_shell *shell)
{
	t_red			*redir;
	int				status;

	redir = cmd->redirections;
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
	return (0);
}
