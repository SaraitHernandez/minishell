/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_tokenize.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sarherna <sarait.hernandez@novateva.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 14:49:26 by sarherna          #+#    #+#             */
/*   Updated: 2024/12/04 15:31:37 by sarherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_operator(t_token *token, char *input, int *index)
{
	if (input[*index] == '|')
		set_token(token, TOKEN_PIPE, "|", index);
	else if (input[*index] == '<')
	{
		if (input[*index + 1] == '<')
			set_token(token, TOKEN_HEREDOC, "<<", index);
		else
			set_token(token, TOKEN_REDIRECT_IN, "<", index);
	}
	else if (input[*index] == '>')
	{
		if (input[*index + 1] == '>')
			set_token(token, TOKEN_REDIRECT_APPEND, ">>", index);
		else
			set_token(token, TOKEN_REDIRECT_OUT, ">", index);
	}
	else
	{
		free(token);
		exit_with_error("Invalid operator");
	}
}

static t_token	*create_token(void)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (!token)
		exit_with_error("Memory allocation failed");
	token->next = NULL;
	return (token);
}

static int	handle_token_end(t_token *token, char *input, int *index)
{
	while (input[*index] && is_whitespace(input[*index]))
		(*index)++;
	if (input[*index] == '\0')
	{
		token->type = TOKEN_EOF;
		token->value = NULL;
		return (1);
	}
	return (0);
}

t_token	*tokenize(char *input, int *index)
{
	t_token	*token;
	int		ret;

	token = create_token();
	if (handle_token_end(token, input, index))
		return (token);
	if (is_operator(input[*index]))
		handle_operator(token, input, index);
	else
	{
		ret = handle_word(token, input, index);
		if (ret == -1)
		{
			free(token);
			return (NULL);
		}
	}
	return (token);
}
