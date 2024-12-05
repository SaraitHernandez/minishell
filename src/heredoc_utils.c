/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sarherna <sarait.hernandez@novateva.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 18:37:31 by sarherna          #+#    #+#             */
/*   Updated: 2024/12/05 18:37:34 by sarherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	setup_heredoc_signal_handlers(struct sigaction *sa_old)
{
	struct sigaction	sa_ignore;

	sigaction(SIGINT, NULL, sa_old);
	sa_ignore.sa_handler = SIG_IGN;
	sigemptyset(&sa_ignore.sa_mask);
	sa_ignore.sa_flags = 0;
	sigaction(SIGINT, &sa_ignore, NULL);
}

static int	fork_error(int *pipe_fd, struct sigaction *sa_old)
{
	close(pipe_fd[0]);
	close(pipe_fd[1]);
	sigaction(SIGINT, sa_old, NULL);
	return (display_error("Failed to fork for heredoc"), 1);
}

static void	heredoc_child_process(t_red *redir, t_shell *shell,
				int *pipe_fd, struct sigaction *sa_old)
{
	sigaction(SIGINT, sa_old, NULL);
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	close(pipe_fd[0]);
	handle_heredoc_child(redir, shell, pipe_fd[1]);
	exit(EXIT_SUCCESS);
}

static int	heredoc_parent_process(pid_t pid, int *pipe_fd,
				struct sigaction *sa_old, t_red *redir)
{
	int	wstatus;

	close(pipe_fd[1]);
	waitpid(pid, &wstatus, 0);
	sigaction(SIGINT, sa_old, NULL);
	if (WIFSIGNALED(wstatus) && WTERMSIG(wstatus) == SIGINT)
	{
		close(pipe_fd[0]);
		return (1);
	}
	else if (WIFEXITED(wstatus) && WEXITSTATUS(wstatus) != 0)
	{
		close(pipe_fd[0]);
		return (1);
	}
	redir->fd = pipe_fd[0];
	return (0);
}

int	handle_single_heredoc(t_red *redir, t_shell *shell)
{
	int					pipe_fd[2];
	pid_t				pid;
	struct sigaction	sa_old;

	if (pipe(pipe_fd) == -1)
		return (display_error("Failed to create pipe"), 1);
	setup_heredoc_signal_handlers(&sa_old);
	pid = fork();
	if (pid == -1)
		return (fork_error(pipe_fd, &sa_old));
	else if (pid == 0)
		heredoc_child_process(redir, shell, pipe_fd, &sa_old);
	else
	{
		if (heredoc_parent_process(pid, pipe_fd, &sa_old, redir))
			return (1);
	}
	return (0);
}
