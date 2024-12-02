/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sarherna <sarait.hernandez@novateva.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 11:58:33 by sarherna          #+#    #+#             */
/*   Updated: 2024/12/01 22:05:05 by sarherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	shell_loop(t_env *env_list)
{
	char	*input;
	t_token	*tokens;
	t_ast	*ast;

	(void)env_list;
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
		ast = parse_tokens(tokens);
		if (check_ast_null(input, tokens, ast))
			continue ;
		if (process_heredocs(ast))
			continue ;
		debug_print(tokens, ast);  //removing this solves the norminette problem
		free_all(3, FREE_STRING, input, FREE_TOKEN, tokens, FREE_AST, ast);
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
