/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sarherna <sarait.hernandez@novateva.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/17 10:07:58 by sarherna          #+#    #+#             */
/*   Updated: 2024/12/10 13:27:40 by sarherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

volatile sig_atomic_t	g_signal_received = 0;

void	sigint_handler(int signo)
{
	(void)signo;
	write(STDOUT_FILENO, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
	g_signal_received = SIGINT;
	rl_done = 1;
}

void	setup_signal_handlers(void)
{
	struct sigaction	sa_int;

	ft_memset(&sa_int, 0, sizeof(sa_int));
	sa_int.sa_handler = sigint_handler;
	sigemptyset(&sa_int.sa_mask);
	sa_int.sa_flags = 0;
	sigaction(SIGINT, &sa_int, NULL);
	signal(SIGQUIT, SIG_IGN);
}

void	heredoc_sigint_handler(int signo)
{
	char	c;

	(void)signo;
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_done = 1;
	rl_redisplay();
	g_signal_received = SIGINT;
	c = '\n';
	ioctl(STDIN_FILENO, TIOCSTI, &c);
}

void	setup_child_signal_handlers(struct sigaction *sa_old)
{
	struct sigaction	sa_ignore;

	sigaction(SIGINT, NULL, sa_old);
	sa_ignore.sa_handler = SIG_IGN;
	sigemptyset(&sa_ignore.sa_mask);
	sa_ignore.sa_flags = 0;
	sigaction(SIGINT, &sa_ignore, NULL);
	signal(SIGQUIT, SIG_IGN);
}
