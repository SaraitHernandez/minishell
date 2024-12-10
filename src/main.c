/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sarherna <sarait.hernandez@novateva.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 11:58:33 by sarherna          #+#    #+#             */
/*   Updated: 2024/12/10 12:59:51 by sarherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_ast	*generate_ast(char *input, t_shell *shell)
{
	t_token	*tokens;
	t_ast	*ast;

	if (check_interrupt(input))
		return (NULL);
	tokens = lexer(input);
	if (!tokens)
		return (NULL);
	expand_tokens(tokens, shell);
	ast = parse_tokens(tokens, shell);
	free_all(2, FREE_STRING, input, FREE_TOKEN, tokens);
	return (ast);
}

static void	run_commands(t_ast *ast, t_shell *shell)
{
	if (!ast)
		return ;
	if (process_heredocs(ast, shell))
	{
		free_all(1, FREE_AST, ast);
		return ;
	}
	execute_ast(ast, shell, NULL);
	free_ast(ast);
}

void	shell_loop(t_shell	*shell)
{
	char	*input;
	t_ast	*ast;

	while (shell->do_exit == 0)
	{
		input = readline("minishell$ ");
		if (!input)
		{
			write(STDERR_FD, "exit\n", 5);
			break ;
		}
		if (*input)
			add_history(input);
		ast = generate_ast(input, shell);
		run_commands(ast, shell);
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
	shell.do_exit = 0;
	shell.in_pipe = 0;
	init_shell_env(envp, &shell);
	shell_loop(&shell);
	rl_clear_history();
	free_env_list(shell.env_list);
	return (shell.exit_status);
}
