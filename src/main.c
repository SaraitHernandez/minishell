/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sarherna <sarait.hernandez@novateva.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 11:58:33 by sarherna          #+#    #+#             */
/*   Updated: 2024/12/04 11:52:36 by sarherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	shell_loop(t_shell	*shell)
{
	char	*input;
	t_token	*tokens;
	t_ast	*ast;

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
		if (check_interrupt(input))
			continue ;
		tokens = lexer(input);
		expand_tokens(tokens, shell);
		ast = parse_tokens(tokens);
		if (check_ast_null(input, tokens, ast))
			continue ;
		if (process_heredocs(ast, shell))
			continue ;
		debug_print(tokens, ast);  //removing this solves the norminette problem
		// Here, in the executor, we need to update shell->exit_status
        // execute_ast(ast, shell);
		free_all(3, FREE_STRING, input, FREE_TOKEN, tokens, FREE_AST, ast);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_shell	shell;

	(void)argc;
	(void)argv;
	setup_signal_handlers();
	shell.env_list = NULL;
    shell.exit_status = 0;
	init_shell_env(envp, &shell);
	shell_loop(&shell);
	rl_clear_history();
	free_env_list(shell.env_list); //-> i need to create a free shell
	return (0);
}
