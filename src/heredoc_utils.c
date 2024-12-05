/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sarherna <sarait.hernandez@novateva.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 17:10:38 by sarherna          #+#    #+#             */
/*   Updated: 2024/12/05 17:53:05 by sarherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handle_heredoc_interrupt(int fd)
{
	close(fd);
	g_signal_received = 0;
	exit(EXIT_FAILURE);
}

void handle_heredoc_child(t_red *redir, t_shell *shell, int write_fd)
{
    char *line;
    int expand;

    // Set default signal handlers
    signal(SIGINT, SIG_DFL);
    signal(SIGQUIT, SIG_DFL);

    expand = !redir->quoted;

    while (1)
    {
        line = readline("> ");
        if (!line)
        {
            // EOF or read error
            break;
        }
        if (ft_strcmp(line, redir->filename) == 0)
        {
            free(line);
            break;
        }
        if (expand)
        {
            char *expanded_line = expand_variable(line, shell);
            free(line);
            line = expanded_line;
        }
        write(write_fd, line, ft_strlen(line));
        write(write_fd, "\n", 1);
        free(line);
    }
    close(write_fd);
}


#include <signal.h>

int handle_single_heredoc(t_red *redir, t_shell *shell)
{
    int pipe_fd[2];
    pid_t pid;
    struct sigaction sa_old, sa_ignore;

    if (pipe(pipe_fd) == -1)
        return (display_error("Failed to create pipe"), 1);

    // Save old SIGINT handler and set to SIG_IGN
    sigaction(SIGINT, NULL, &sa_old);
    sa_ignore.sa_handler = SIG_IGN;
    sigemptyset(&sa_ignore.sa_mask);
    sa_ignore.sa_flags = 0;
    sigaction(SIGINT, &sa_ignore, NULL);

    pid = fork();
    if (pid == -1)
    {
        close(pipe_fd[0]);
        close(pipe_fd[1]);
        // Restore old SIGINT handler before returning
        sigaction(SIGINT, &sa_old, NULL);
        return (display_error("Failed to fork for heredoc"), 1);
    }
    else if (pid == 0)
    {
        // Child process
        // Restore old SIGINT handler in child
        sigaction(SIGINT, &sa_old, NULL);
        // Set default signal handlers in child
        signal(SIGINT, SIG_DFL);
        signal(SIGQUIT, SIG_DFL);

        close(pipe_fd[0]); // Close read end in child
        handle_heredoc_child(redir, shell, pipe_fd[1]);
        exit(EXIT_SUCCESS);
    }
    else
    {
        // Parent process
        int wstatus;

        close(pipe_fd[1]); // Close write end in parent

        // Wait for child process
        waitpid(pid, &wstatus, 0);

        // Restore old SIGINT handler in parent
        sigaction(SIGINT, &sa_old, NULL);

        if (WIFSIGNALED(wstatus) && WTERMSIG(wstatus) == SIGINT)
        {
            // Heredoc was interrupted
            close(pipe_fd[0]);
            return (1);
        }
        else if (WIFEXITED(wstatus) && WEXITSTATUS(wstatus) != 0)
        {
            // Child exited with error
            close(pipe_fd[0]);
            return (1);
        }
        // Success
        redir->fd = pipe_fd[0];
        return (0);
    }
}