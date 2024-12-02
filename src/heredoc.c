/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sarherna <sarait.hernandez@novateva.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 15:38:38 by sarherna          #+#    #+#             */
/*   Updated: 2024/12/02 21:22:40 by sarherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handle_heredoc_interrupt(int fd)
{
	close(fd);
	g_signal_received = 0;
	return (1);
}

int	handle_single_heredoc(t_red *redir)
{
	char	*line;
	int		pipe_fd[2];

	if (pipe(pipe_fd) == -1)
	{
		display_error("Failed to create pipe");
		return (1);
	}
	setup_heredoc_signal_handlers();
	while (1)
	{
		line = readline("> ");
		if (!line || ft_strcmp(line, redir->filename) == 0)
			break ;
		write(pipe_fd[1], line, ft_strlen(line));
		write(pipe_fd[1], "\n", 1);
		free(line);
	}
	free(line);
	close(pipe_fd[1]);
	setup_signal_handlers();
	if (g_signal_received == SIGINT)
		return (handle_heredoc_interrupt(pipe_fd[0]));
	redir->fd = pipe_fd[0];
	return (0);
}

int	process_heredocs(t_ast *cmd)
{
	t_red			*redir;
	int				status;

	redir = cmd->redirections;
	while (redir)
	{
		if (redir->type == TOKEN_HEREDOC)
		{
			status = handle_single_heredoc(redir);
			if (status != 0)
				return (status);
		}
		redir = redir->next;
	}
	return (0);
}
