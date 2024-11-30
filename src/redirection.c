/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sarherna <sarait.hernandez@novateva.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 15:38:38 by sarherna          #+#    #+#             */
/*   Updated: 2024/11/30 18:33:30 by sarherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*dup_delimiter(t_ast *heredoc_node, t_token *tokens, t_ast *ast)
{
	char	*delimiter;

	delimiter = ft_strdup(heredoc_node->filename);
	if (!delimiter)
		free_all(3, FREE_TOKEN, tokens, FREE_AST, ast, ERROR_MSG, "MemFailed");
	return (delimiter);
}

int	handle_heredoc(t_ast *heredoc_node, t_token *tokens, t_ast *ast)
{
	char	*delimiter;
	char	*heredoc_line;

	delimiter = dup_delimiter(heredoc_node, tokens, ast);
	setup_heredoc_signal_handlers();
	while (1)
	{
		heredoc_line = readline("> ");
		if (!heredoc_line || ft_strcmp(heredoc_line, delimiter) == 0)
		{
			free_all(2, FREE_STRING, heredoc_line, FREE_STRING, delimiter);
			break ;
		}
		if (g_signal_received == SIGINT)
		{
			g_signal_received = 0;
			free_all(2, FREE_STRING, heredoc_line, FREE_STRING, delimiter);
			setup_signal_handlers();
			return (1);
		}
		heredoc_node->heredoc_content = concat_content(
				heredoc_node->heredoc_content, heredoc_line);
	}
	setup_signal_handlers();
	return (0);
}

void	reset_terminal_settings(void)
{
	struct termios	term_attrs;

	if (tcgetattr(STDIN_FILENO, &term_attrs) == 0)
	{
		term_attrs.c_lflag |= (ECHO | ICANON);
		tcsetattr(STDIN_FILENO, TCSANOW, &term_attrs);
	}
}
