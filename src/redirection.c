/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akacprzy <akacprzy@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 21:52:46 by sarherna          #+#    #+#             */
/*   Updated: 2024/12/08 15:05:07 by akacprzy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	redirect_input(char *filename)
{
	int	fd;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
	{
		redir_error(filename);
		return (1);
	}
	if (dup2(fd, STDIN_FILENO) == -1)
	{
		redir_error(filename);
		return (1);
	}
	close(fd);
	return (0);
}

int	redirect_output(char *filename, int flags)
{
	int	fd;

	fd = open(filename, O_WRONLY | O_CREAT | flags, 0644);
	if (fd == -1)
	{
		redir_error(filename);
		return (1);
	}
	if (dup2(fd, STDOUT_FILENO) == -1)
	{
		redir_error(filename);
		return (1);
	}
	close(fd);
	return (0);
}

static int	handle_heredoc_redirection(t_red *redirs)
{
	if (dup2(redirs->fd, STDIN_FILENO) == -1)
	{
		display_error("minishell: Failed to redirect heredoc output");
		return (1);
	}
	close(redirs->fd);
	return (0);
}

int	handle_redirection(t_red *redirs)
{
	if (redirs->type == TOKEN_HEREDOC)
		handle_heredoc_redirection(redirs);
	if (redirs->type == TOKEN_REDIRECT_IN)
	{
		if (redirect_input(redirs->filename) != 0)
			return (1);
	}
	else if (redirs->type == TOKEN_REDIRECT_OUT)
	{
		if (redirect_output(redirs->filename, O_TRUNC) != 0)
			return (1);
	}
	else if (redirs->type == TOKEN_REDIRECT_APPEND)
	{
		if (redirect_output(redirs->filename, O_APPEND) != 0)
			return (1);
	}
	return (0);
}
