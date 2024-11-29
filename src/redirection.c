/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sarherna <sarait.hernandez@novateva.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 15:38:38 by sarherna          #+#    #+#             */
/*   Updated: 2024/11/17 18:53:07 by sarherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handle_heredoc(t_ast *heredoc_node, t_token *tokens, t_ast *ast)
{
	char	*delimiter;
	char	*heredoc_line;

	delimiter = strdup(heredoc_node->filename);
	if (!delimiter)
	{
		free_tokens(tokens);
		free_ast(ast);
		exit_with_error("Memory allocation failed for delimiter");
	}
	setup_heredoc_signal_handlers();
	while (1)
	{
		heredoc_line = readline("> ");
		if (g_signal_received == SIGINT)
		{
			g_signal_received = 0;
			free(heredoc_line);
			free(delimiter);
			free_tokens(tokens);
			free_ast(ast);
			setup_signal_handlers();
			return (1);
		}

		if (!heredoc_line)
		{			
            free(delimiter);
			break ;
		}

		if (strcmp(heredoc_line, delimiter) == 0)
		{
			free(heredoc_line);
			free(delimiter);
			break ;
		}
		heredoc_node->heredoc_content = concat_content(heredoc_node->heredoc_content, heredoc_line);
	}
	setup_signal_handlers();
	return (0);
}