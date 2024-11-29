/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sarherna <sarait.hernandez@novateva.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 11:58:33 by sarherna          #+#    #+#             */
/*   Updated: 2024/11/24 22:04:45 by sarherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	shell_loop(t_env *env_list)
{
	char	*input;
	t_token	*tokens;
	t_ast	*ast;
	t_ast	*last_child;
	t_ast	*heredoc_node;

	(void)env_list;
	heredoc_node = NULL;
	while (1)
	{
		input = readline("minishell$ ");
		if (!input)
		{
			write(STDOUT_FILENO, "exit\n", 5);
			break ;
		}
		if (*input)
			add_history(input);
		if (g_signal_received == SIGINT)
		{
			g_signal_received = 0;
			free(input);
			continue ;
		}
		tokens = lexer(input);
		print_tokens(tokens);
		ast = parse_tokens(tokens);
		last_child = last_left_child(ast);
		if (ast->type == NODE_HEREDOC)
			heredoc_node = ast;
		else if ((last_child && last_child->type == NODE_HEREDOC))
			heredoc_node = last_child;
		if (heredoc_node)
			handle_heredoc(heredoc_node, tokens, ast);
		print_ast(ast);
		free_tokens(tokens);
		free_ast(ast);
		free(input);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_env	*env_list;

	(void)argc;
	(void)argv;
	setup_signal_handlers();
	init_shell_env(envp, &env_list);
	shell_loop(env_list);
	rl_clear_history();
	free_env_list(env_list);
	return (0);
}
