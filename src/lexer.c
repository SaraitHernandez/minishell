/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sarherna <sarait.hernandez@novateva.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 16:36:40 by sarherna          #+#    #+#             */
/*   Updated: 2024/12/04 13:49:23 by sarherna         ###   ########.fr       */
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

int	handle_word(t_token *token, char *input, int *index)
{
	int		start;
	int		quote;
	char	*value;
	char	*part;
	int		ret;

	start = *index;
	quote = 0;
	value = ft_strdup("");
	part = NULL;
	while (input[*index] && !is_whitespace(input[*index]) && !is_operator(input[*index]))
	{
		if (is_quote(input[*index]))
		{
			ret = handle_quote(input, index, &part, &quote);
			if (ret == -1)
			{
				free(value);
				return -1;
			}
			value = ft_strjoin_free(value, part);
			free(part);
		}
		else
		{
			start = *index;
			while (input[*index] && !is_whitespace(input[*index]) && !is_operator(input[*index]) && !is_quote(input[*index]))
				(*index)++;
			part = ft_strndup(&input[start], *index - start);
			value = ft_strjoin_free(value, part);
			free(part);
		}
	}
	token->type = TOKEN_WORD;
	token->quoted = quote;
	token->value = value;
	if (!token->value)
		free_all(2, FREE_TOKEN, token, ERROR_MSG, "Memory allocation failed");
	return (0);
}

t_token	*tokenize(char *input, int *index)
{
	t_token	*token;
	int ret;

	token = malloc(sizeof(t_token));
	if (!token)
		exit_with_error("Memory allocation failed");
	token->next = NULL;
	while (input[*index] && is_whitespace(input[*index]))
		(*index)++;
	if (input[*index] == '\0')
	{
		token->type = TOKEN_EOF;
		token->value = NULL;
		return (token);
	}
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

t_token	*lexer(char *input)
{
	t_token	*head;
	t_token	*current;
	t_token	*new_token;
	int		index;

	head = NULL;
	current = NULL;
	index = 0;
	while (1)
	{
		new_token = tokenize(input, &index);
		if(!new_token)
		{
			free_tokens(head);
			return (NULL);
		}
		if (!head)
		{
			head = new_token;
			current = new_token;
		}
		else
		{
			current->next = new_token;
			current = new_token;
		}
		if (new_token->type == TOKEN_EOF)
			break ;
	}
	return (head);
}
